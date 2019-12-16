import * as querystring from "query-string";
import { deviceFetch } from "./common.js";

export const CallFunction = (name, argument) => 
    deviceFetch(name, {
        method: "post",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            arg: argument
        })
    });
