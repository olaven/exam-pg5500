import * as React from "react"; 
import { Container, Header, Segment, Button } from "semantic-ui-react";
import { getVariable } from "../../fetchers/GetVariable.jsx";

const useForceUpdate = () => {

    const [tick, setTick] = React.useState(0);
    const update = React.useCallback(() => {
        console.log("updating");
        setTick(tick + 1);
    }, []);

    return update; 
}

const StatusElement = props => {

    const {displayName, variableName} = props; 
    const value = getVariable(variableName); 
    const update = useForceUpdate(); 
    
    return <Segment>
        <Header >{displayName}</Header>
        <Header as="h2">{(value || value === 0)? value: "loading..."}</Header>
        <Button onClick={update} icon="refresh"/>
    </Segment>
}


export const Status = () => <Container>
    {[
        ["Custom message"     , "message"            ],
        ["Alarm hour"         , "alarm_hour"         ],
        ["Alarm minute"       , "alarm_minute"       ],
        ["Background color"   , "background_color"   ],
        ["Text color"         , "text_color"         ],
        ["Temperature inside" , "inside_temperature" ],
        ["Temperature outside", "outside_temperature"],
    ].map(pair => <StatusElement key={pair[0]} displayName={pair[0]} variableName={pair[1]}/>)
}
</Container>