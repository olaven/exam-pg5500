import * as React from "react";
import { CallFunction } from "../../fetchers/CallFunction.jsx";
import { Segment, Header, Button, Input, Dropdown } from "semantic-ui-react";
import { getStops } from "../../fetchers/GetStops.jsx";
import { getVariable } from "../../fetchers/GetVariable.jsx";


export const TextSetting = props => {

    const { variableName, displayName, functionName } = props;

    const [argument, setArgument] = React.useState(null);
    const {value} = getVariable(variableName); 

    const onClick = () => {
        
        CallFunction(functionName, argument); //TODO: visual feedback/reload
    };

    return <Segment>
        <Header>{displayName}</Header>
        <Input placeholder={value} type={"text"} onChange={(event) => { setArgument(event.target.value) }} />
        <Button onClick={onClick} primary>OK</Button>
    </Segment>
}

export const ToggleSetting = props => {

    const { displayName, functionName } = props;

    const onClick = () => {

        CallFunction(functionName); 
    }

    return <Segment>
        <Header>{displayName}</Header>
        <Button onClick={onClick} primary>Toggle</Button>
    </Segment>
}

export const ArriveBySetting = () => {

    const [hour, setHour] = React.useState(9);
    const [minute, setMinute] = React.useState(15);

    const hourOptions = [...Array(24).keys()].map(i => { return { key: i, text: i, value: i } })
    const minuteOptions = [...Array(60).keys()].map(i => { return { key: i, text: i, value: i } })

    const onClick = () => {
        
        CallFunction("change_arrive_by_hour", hour);
        CallFunction("change_arrive_by_minute", minute);
    }

    return <Segment>
        <Header as={"h2"}>When do you need to arrive?</Header>
        <Dropdown placeholder={"09"} search options={hourOptions} onChange={(event) => { setHour(parseInt(event.target.innerText))}}/>
        <Dropdown placeholder={"15"} search options={minuteOptions} onChange={(event) => { setMinute(parseInt(event.target.innerText)) }} />
        <Button primary onClick={onClick}>OK</Button>        
    </Segment>
}

export const ExtraTimeSetting = () => {

    const [minutes, setMinute] = React.useState(25);
    const minuteOptions = [...Array(60).keys()].map(i => { return { key: i, text: i, value: i } })

    const onClick = () => {

        CallFunction("change_extra_minutes", minutes); 
    }

    return <Segment>
        <Header as={"h2"}>How much extra time do you need?</Header>
        <Dropdown placeholder={"25"} search options={minuteOptions} onChange={(event) => { setMinute(parseInt(event.target.innerText)) }} />
        <Button primary onClick={onClick}>OK</Button>
    </Segment>
}

export const PlaceInput = props => {

    const { displayName, functionName } = props; 

    const [name, setName] = React.useState("Oslo"); 
    const [id, setId] = React.useState(null);

    const stops = getStops(name);

    const onClick = () => {

        CallFunction(functionName, id);
    }

    const onChange = (_, data) => {

        const id = data.value; 
        setId(id); 
    }

    const onSearchChange = (event) => {

        const name = event.target.value; 
        setName(name);
    }

    return <Segment>
        <Header as="h2">{displayName}</Header>
        <Dropdown
            clearable
            fluid
            search
            selection
            options={stops}
            placeholder={"Select place"}
            onChange={onChange}
            onSearchChange={onSearchChange}
        />
        <Button primary onClick={onClick}>OK</Button>
    </Segment>; 
}