import * as React from "react"; 
import { Container, Button, Segment, Input, Header } from "semantic-ui-react";
import { TextSetting, ArriveBySetting, ExtraTimeSetting, PlaceInput } from "./SettingsInput.jsx";

const Alarm = () => <Segment>
    <Header as="h1">Alarm settings</Header>
    <ArriveBySetting />
    <ExtraTimeSetting />
    <PlaceInput displayName="Change your starting location" functionName={"change_alarm_from_location"}/>
    <PlaceInput displayName="Change your destination" functionName={"change_alarm_to_location"} />
</Segment>

const General = () => <Segment>
    <Header as={"h1"}>General settings</Header>
    {[
        ["Change text color", "change_text_color"],
        ["Change background color", "change_text_color"],
        ["Change temperature city", "change_temperature_city"],
        ["Update custom message", "update_message"]
    ].map(pair => <TextSetting key={pair[0]} displayName={pair[0]} functionName={pair[1]} />)}
</Segment>

export const Settings = () => <Container>
        <Alarm/>
        <General/>
    </Container>