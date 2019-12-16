import * as React from "react"; 
import { Container, Header, Segment } from "semantic-ui-react";
import { getVariable } from "../fetchers/GetVariable.jsx";

const StatusElement = props => {

    const {displayName, variableName} = props; 
    const value = getVariable(variableName); 
    
    return <Segment>
        <Header >{displayName}</Header>
        <Header as="h2">{(value || value === 0)? value: "loading..."}</Header>
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