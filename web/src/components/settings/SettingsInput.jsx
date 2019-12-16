import * as React from "react";
import { CallFunction } from "../../fetchers/CallFunction.jsx";
import { Segment, Header, Button, Input, Dropdown } from "semantic-ui-react";


export const TextSetting = props => {

    const [argument, setArgument] = React.useState(null);
    const { displayName, functionName } = props;

    const onClick = async () => {
        console.log("argument", argument);
        await CallFunction(functionName, argument); //TODO: visual feedback/reload
    };

    return <Segment>
        <Header>{displayName}</Header>
        <Input type={"text"} onChange={(event) => { setArgument(event.target.value) }} />
        <Button onClick={onClick} primary>OK</Button>
    </Segment>
}

export const ArriveBySetting = props => {

    const [hour, setHour] = React.useState(9);
    const [minute, setMinute] = React.useState(15);

    const hourOptions = [...Array(24).keys()].map(i => { return { key: i, text: i, value: i } })
    const minuteOptions = [...Array(60).keys()].map(i => { return { key: i, text: i, value: i } })

    const onClick = () => {
        
        CallFunction("change_arrive_by_hour", hour);
        CallFunction("change_arrive_by_minute", minute);
    }

    return <Segment>
        <Dropdown placeholder={"09"} search options={hourOptions} onChange={(event) => { setHour(parseInt(event.target.innerText))}}/>
        <Dropdown placeholder={"15"} search options={hourOptions} onChange={(event) => { setMinute(parseInt(event.target.innerText)) }} />
        <Button primary onClick={onClick}>OK</Button>        
    </Segment>
}