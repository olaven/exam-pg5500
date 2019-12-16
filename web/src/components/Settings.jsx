import * as React from "react"; 
import { Container, Button } from "semantic-ui-react";
import { CallFunction } from "../fetchers/CallFunction.jsx";

export const Settings = () => {

    const test = async () => {
        const response = await CallFunction("change_background_color", "yellow"); 

        console.log(response);
    }

    return <Container>
        <Button onClick={test}>change color to yellow</Button>
    </Container>
}