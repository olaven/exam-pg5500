const webpack = require("webpack");
var dotenv = require('dotenv').config({
    path: __dirname + '/.env'
});

module.exports = () => {

    console.log(dotenv);
    return {
        entry: ['babel-polyfill', './src/index.js'],
        module: {
            rules: [
                {
                    test: /\.(js|jsx)$/,
                    exclude: /node_modules/,
                    use: ['babel-loader']
                }
            ]
        },
        resolve: {
            extensions: ['.js', '.jsx']
        },
        output: {
            path: __dirname + '/dist',
            publicPath: '/',
            filename: 'bundle.js'
        },
        devServer: {
            contentBase: './dist',
            historyApiFallback: true, //avoiding 404 when refreshing
        },
        plugins: [
            new webpack.DefinePlugin({
                "process.env": JSON.stringify(dotenv.parsed)
            }),
        ]
    };
};