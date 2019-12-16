import * as React from "react"; 
import { Header, Container, Segment, Grid, Divider, Button } from "semantic-ui-react";
import { Status } from "./status/Status.jsx";
import { Settings } from "./settings/Settings.jsx";

export const App = () => <Container>
    <Header as={"h1"} color={"blue"}>GUI - iot-alarm</Header> 

    <Segment>
        <Grid columns={2} relaxed='very' stackable>
            <Grid.Column verticalAlign='middle'>
                <Settings />
            </Grid.Column>
            <Grid.Column>
                <Status />
            </Grid.Column>
        </Grid>

        <Divider vertical/>
    </Segment>
</Container>