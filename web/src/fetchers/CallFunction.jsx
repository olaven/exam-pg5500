import * as React from "react"; 
import { deviceFetch } from "./common.js";

export const CallFunction = (name, argument) => {

    return deviceFetch(name, { 
        method: "post",
        body: JSON.stringify({
            arg: argument
        })
    }); 
}