import * as React from "react"; 

/**
 * Searches "Nasjonalt Stoppestedsregister" (https://developer.entur.org/pages-nsr-nsr)
 * For stops based on the given name. 
 * @param {string} name 
 * @returns {[key: string, value: string, text: string]} places
 */
export const getStops = (name) => {

    const [stops, setStops] = React.useState([]); 
    React.useEffect(() => {

        const fetchPlaces = async () => {
            const query = `
                {
                    stopPlace(query: "${name}") {
                        topographicPlace {
                            name {
                                value
                            }
                        }
                        id
                        name {
                            value
                        }
                    }
                }
            `

            const response = await fetch("https://api.entur.io/stop-places/v1/graphql", {
                method: "post", 
                headers: {
                    "content-type": "application/json"
                },
                body: JSON.stringify({ query })
            }); 

            if (response.status === 200) {
                
                const data = (await response.json()).data; 
                const converted = data.stopPlace.map(place => {

                    const id = place.id.split(":")[2]; //NOTE: assumes standard: NSR:StopPlace:ID_VALUE
                    return {
                        key: id,
                        value: id, 
                        text: `${place.name.value} - ${place.topographicPlace.name.value}`
                    }
                });

                setStops(converted);
            } else {

                console.error("failed to fetch places from entur.");
            }
        }

        fetchPlaces();
    }, [name]);

    return stops; 
}