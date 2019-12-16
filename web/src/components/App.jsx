import * as React from "react"; 
import { Header, Container, Segment, Grid, Divider } from "semantic-ui-react";
import { Status } from "./Status.jsx";
import { Settings } from "./Settings.jsx";

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