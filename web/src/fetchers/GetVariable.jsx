import * as React from "react"; 
import { deviceFetch } from "./common.js";

export const getVariable = (name) => {


    const [ value, setValue ] = React.useState(null); 

    React.useEffect(() => {

    
        const fetchVariable = async () => {

            const response = await deviceFetch(name, {});
            if (response.status === 200) {

                const json = await response.json();
                setValue(json.result);
            } else {

                setValue(null);
            }
        }

        fetchVariable(); 
    }, [name]);

    return value; 
}