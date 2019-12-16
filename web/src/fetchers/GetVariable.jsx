import * as React from "react"; 
import { deviceFetch } from "./common.js";

export const getVariable = (name) => {


    const [ value, setValue ] = React.useState(null); 
    
    const fetchVariable = async () => {

        const response = await deviceFetch(name, {});
        if (response.status === 200) {

            const json = await response.json();
            setValue(json.result);
        } else {

            setValue(null);
        }
    }

    React.useEffect(() => {fetchVariable()}, [name]);
    const update = React.useCallback(fetchVariable, [])

    return { value, update }; 
}