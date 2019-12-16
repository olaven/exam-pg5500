import * as React from "react"; 
import { Container, Button, Segment, Input, Header } from "semantic-ui-react";
import { TextSetting, ArriveBySetting, ExtraTimeSetting, PlaceInput, ToggleSetting } from "./SettingsInput.jsx";

const Alarm = () => <Segment>
    <Header as="h1">Alarm settings</Header>
    <ArriveBySetting />
    <ExtraTimeSetting />
    <PlaceInput displayName="Change your starting location" functionName={"change_alarm_from_location"}/>
    <PlaceInput displayName="Change your destination" functionName={"change_alarm_to_location"} />
</Segment>

const General = () => <Segment>
    <Header as={"h1"}>General settings</Header>
    <ToggleSetting displayName="Toggle alarm" functionName="toggle_alarm_enabled" />
    {[
        ["Change text color", "change_text_color", "text_color"],
        ["Change background color", "change_background_color", "background_color"],
        ["Change temperature city", "change_temperature_city", "temperature_city"],
        ["Update custom message", "update_message", "message"]
    ].map(triple => <TextSetting key={triple[0]} displayName={triple[0]} functionName={triple[1]} variableName={triple[2]}/>)}
    <ToggleSetting displayName="Toggle christmas mode" functionName="toggle_christmas_mode" />
</Segment>

export const Settings = () => <Container>
        <Alarm/>
        <General/>
    </Container>
