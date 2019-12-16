
/**
 * Acts upon a variable/function of device.
 * @param {string} name name of variable or function
 * @param {any} options additional fetch-options
 */
export const deviceFetch = (name, options) => {

    const { DEVICE_ID, ACCESS_TOKEN } = process.env;
    const url = `https://api.particle.io/v1/devices/${DEVICE_ID}/${name}?arg=blue`;
    
    options.headers = {
        ...options.headers, 
        "Authorization": `Bearer ${ACCESS_TOKEN}`
    }
    return fetch(url, options); 
}