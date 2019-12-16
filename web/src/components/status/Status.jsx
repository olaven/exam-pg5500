import * as React from "react"; 
import { Container, Header, Segment, Button } from "semantic-ui-react";
import { getVariable } from "../../fetchers/GetVariable.jsx";

const StatusElement = props => {

    const {displayName, variableName} = props; 
    const { value, update } = getVariable(variableName); 
    
    return <Segment>
        <Header >{displayName}</Header>
        <Header as="h2">{(value || value === 0)? value: "loading..."}</Header>
        <Button onClick={update} icon="refresh"/>
    </Segment>
}


export const Status = () => <Container>
    {[
        ["Custom message"              , "message"            ],
        ["Hour of next alarm:"         , "alarm_hour"         ],
        ["Minute of next alarm:"       , "alarm_minute"       ],
        ["Extra time (minutes)"        , "extra_minutes"      ],
        ["Background color"            , "background_color"   ],
        ["Text color"                  , "text_color"         ],
        ["Temperature inside"          , "inside_temperature" ],
        ["Temperature outside (in chosen city)", "outside_temperature"],
    ].map(pair => <StatusElement key={pair[0]} displayName={pair[0]} variableName={pair[1]}/>)
}
</Container>