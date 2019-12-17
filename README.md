# Dokumentasjon - Eksamen, embedded systems

## Hva jeg har laget
Jeg har valgt oppgave B. Med andre ord har oppgaven vært å lage en IOT-dings som
har en eller annen form for nytte- eller underholdningsverdi. Oppgaven spesifiser
at man skal bruke [Particle Photon](https://docs.particle.io/datasheets/wi-fi/photon-datasheet/). 

### Kjernefunksjonalitet

Helt konkret har jeg laget en nattbordsalarm, med litt ekstra funksjonalitet. 
Hovedideen er at alarmen skal vekke deg på det tidspunktet du må stå opp for 
å rekke å komme deg dit du skal, med kollektivtransport. Den stilles altså ikke 
på tidspunkt for vekking (direkte), men heller på hvor du skal reise fra, 
hvor du skal reise til og ikke minst når du skal ankomme din destinasjon. 

En viktig del av konseptet er at den er oppdatert på sanntidsdata. På den måten
vil alarmen vekke brukeren tidligere/senere dersom det oppstår endringer i
kollektivtransporten i løpet av natten, gjennom en integrasjon med [Entur](entur.no)

Starten på min dag styres i stor grad av hvilken bane jeg må rekke, til dagens
forelesning. Jeg bruker meget kort tid hjemme før jeg drar, og spiser ofte
frokost på veien. Med andre ord står jeg mer eller mindre opp til T-banen. 
Det er mange positive sider for dette for en student som ikke liker morgener, 
men det betyr at jeg er sårbar for forsinkelser og endringer i rutetabeller. 

Dette har jeg brent meg på flere ganger, og det hender at jeg er litt for sent
ute til forelesning, som jeg aller helst vil unngå. 
Det betyr også at vekkealarmene mine knyttes tett opp til rutetider - det er
nyttig for meg å få kombinert rutetider og vekking i samme "dings". At den i 
tillegg kan justere seg etter forsinkelser mer eller mindre i sanntid, er en 
stor bonus.

Nytteverdien i denne løsningen er derfor høyst reell for meg. 


Alarmen kan konfigureres gjennom et webgrensesnitt (i [./web](./web)), blant
annet. Webgrensesnittet blir beskrevet nærmere [senere](#webgrensesnitt). 
Man kan også konfigurere alarmen gjennom funksjoner som er tilgjengelige
i Particle sin
app([iOS](https://apps.apple.com/us/app/particle-iot/id991459054) og [Android](https://play.google.com/store/apps/details?id=io.particle.android.app&hl=en_US)). 

### Øvrig funksjonalitet
I tillegg til denne kjernefunksjonaliteten, har jeg laget annen
ekstra-funksjonalitet i tillegg, som jeg skal beskrive i kommende avsnitt. 

* Alarmen har en skjerm som til en hver tid viser et alarmens status til brukeren. 
Brukergrensesnittet består av forskjellige "skjermer" (moduser, vinduer e.l.)
som viser forskjellig informasjon. Man kan bytte mellom disse med å trykke på 
frem- og tilbake-knapper. Når man bytter, spilles det en liten tone for å gi
tilbakemelding til brukeren. 

* Følgende skjermer er tilgjengelig: 
 1. Temperatur
    * Viser temperaturen inne, som leses med en sensor
    * Viser temperaturen i egenkonfigurert by (via. webhook TODO: link til senere omtale
     avwebhooks) 
 2. Alarm 
    * Viser tidspunktet for neste alarm 
 3. Melding
    * Viser en egen hilsen, som brukeren kan legge inn selv (":-)" som default).
      Tanken min er at dette kan være et notat e.l. om noe man skal huske om morgenen.
 4. Klokke
    * Viser nåværende klokkeslett, dag og måned
   
* Det er mulig å endre bakgrunns- og tekstfarge via "Particle Cloud Functions",
  for eksempel via webgrensesnittet. 

* I et forsøk på å varsle om skader, vil alarmen dessuten sende mail (TODO:
  valgfri epost.) dersom alarmen blir utsatt for flamme eller vann. Dette gjøres 
  med tilkoblet vann- og flammesensor, og integrasjon med
  [Mailgun](https://www.mailgun.com/).
  Det vil være katastrofalt for alarmen dersom den blir utsatt for noen av disse 
  tingene, og derfor gjelder det å si ifra. Det er også ment som en liten
  "homage" til [denne scenen](https://youtu.be/xqQ6Z-HmAqY?t=47). Dersom man plasserer alarmen litt taktisk, 
  kan man jo tenke seg at vannsensoren ville plukke opp potensielle vannskader
  før de ble kritiske for huset.
  Underholdningsverdien rundt det å sende mail ved en slik krise er kanskje vel
  så relevant for oppgaven som noen potensiell "nytteverdi".  
  
* Julemodus - Jeg har lagt inn en sesongaktuell julemoduls, som kan aktiveres
  via via grensesnitt/functions. Alarmen spiller en liten julesang og har fine 
  LED-lys i julefarger. Dette er en ren underholdningsfeature for en juleelsker
  som meg selv, for å gi ekstra god stemning i eksamensperioden! 

### Eksponering av data 
Jeg har hatt en baktanke om at oppgaven fokuserer på IoT.
Det betyr at jeg ikke har hatt et veldig stort fokus på sensorer og oppkoblinger 
med mindre jeg har sett nyttige, morsome eller koselige bruksområder. 

Den dataen som behandles av dingsen, gjøres stort sett tilgjengelig via [Cloud
Functions](https://docs.particle.io/reference/device-os/firmware/photon/#cloud-functions). 
Dette gjør at man ikke er begrenset til det selve mikrokontrolleren kan gjøre
med dataen, men at man kan bygge masse tjenester og integrasjoner i samspill med
det som skjer på Photon-devicen. Webgrensesnittet jeg har laget er et eksempel
på dette. 

Dersom man eier de rette nøklene og eier dingsen, gis det tilgang på publiserte
variable, funksjoner og events. Jeg har valgt å gjøre events private, som vil si
at andre ikke får tilgang på dem. I mitt tilfelle er eventene som sendes i
utgangspuktet bare av interesser for meg, og ikke for andre. 

Jeg eksponerer data om følgende: 
* Nåværende tidspunkt for alarm 
* Ekstra tid man trenger til nærmeste stopp 
* Stasjoner for avreise og ankomst 
* Når man ønsker å ankomme innen 
* Informasjon om temperature, som valgt by, og temperaturene som leses 
* Hvorvidt alarmen er aktivert eller ikke 
* Nåværende fargekonfigurasjoner 
* Nåværende egendefinert melding
* E-post som skal få mail ved skadevarsel

Det eksponeres også relevant funksjonalitet for å endre på denne dataen, som gir 
masse muligheter for å bygge videre i fremtiden. Har man flere dingser, kan 
man kombinere flere ting, og få desto flere muligheter. 

Tilkoblingen til nett gjør dessuten at man kan koble andre løsninger på sin
egen. Dette er svært viktig for min løsning, i og med at kjernefunksjonaliteten 
bygger på Entur sitt [API for reiseplanlegging](https://developer.entur.org/pages-journeyplanner-journeyplanner).
Jeg benytter meg også av [Mailgun sitt API]. Disse tjenestene skriver jeg mer om 
under [integrasjoner](#integrasjoner). 

## Oppsett 
* `cd particle && particle flash DEVICE_NAME`


### Webgrensesnitt
For å gjøre løsningen mer tilgjengelig for brukeren, har jeg laget et lite
segrensesnitt som gjør et enklere å konfigurere alarmen. Her kan man endre
innstillinger, og se status på alarmen. Grensesnittet kjører HTTP-kall mot 
[Particle Device Cloud
API](https://docs.particle.io/reference/device-cloud/api/), og står helt fritt 
fra den fysiske dingsen. Grensesnittet kommuniserser også med [entur sitt
API](https://developer.entur.org/pages-nsr-nsr) for Nasjonalt
Stoppestedsregister, for å gjøre det mer brukervennlig å endre stoppesteder.

#### Oppsett 
* en `.env`-fil i `./web` som inneholder følgende: 
  * `DEVICE_ID=my_device_id` (se på dine "devices" i [Particle IDE](https://build.particle.io/build/new))
  * `ACCESS_TOKEN=my_access_token`(se [her](https://docs.particle.io/reference/device-cloud/api/#generate-an-access-token))
* installer `node` og `yarn`/`npm`
* kjøre `yarn dev`/`npm run dev` i `./web`
 
## Integrasjoner
Jeg har benyttet av Particle sin integrasjonsløsning for å hente data fra andre
tjenester over nettet. Rent konkret har jeg brukt tjenestene:
* [Entur sin
reiseplanlegger](https://developer.entur.org/pages-journeyplanner-journeyplanner) 
* [OpenWeather](https://openweathermap.org/api) for værdata
* [Mailgun](https://www.mailgun.com/) for å sende mail 

Dette har jeg gjort ved å opprette webhooks i Particle Cloud. Når en webhook
trigges, kjører den noe som kan tenkes på som et HTTP-"callback". Hvilken URL som skal kalles og
akkurat hva som skal skje ("hva slags callback det skal være"), utgjør
definisjonen på hver enkelt webhook. Triggingen av et callback gjør Particle
gjennom et "event-system". 

En webhook er litt som å trigge et "callback" med å kalle en URL. Hvilken URL
som skal kalles og akkurat hva som skal skje ("hva slags callback det skal
være"), utgjør definisjonen på hver enkelt webhook. Triggingen av et callback
gjør Particle gjennom et "event-system". 

Events kan publiseres fra particle med `Particle.publish`-metoden. Webhooks kan
tolke data sendt i `publish` med å bruke [variable
substitution](https://docs.particle.io/reference/device-cloud/webhooks/#variable-substitution)
og [Moustache Templates](mustache.github.io/mustache.5.html). 

På tilsvarende måte kan man abbonnere (`subscribe`) på svar fra webhook-kallet
("callback-et"). Da bruker man [Response
Templates](https://docs.particle.io/reference/device-cloud/webhooks/#receiving-complex-data)
for å tolke dataen. Den ferdigtolkede dataen kommer så inn i en handler i
particle-koden. 


Events kan publiseres fra particle med `Particle.publish("my_event", data,
PRIVATE)`nt-system". . Webhooks kan tolke data me kan tolke data sendt i
`publish` med å bruke [Variable
Substitution](https://docs.particle.io/reference/device-cloud/webhooks/#receiving-complex-data)
og [Moustache
Templates](https://docs.particle.io/reference/device-cloud/webhooks/#receiving-complex-data).

På tilsvarende måte kan man abbonnere (`subscribe`På samme måte  på svar fra
webhook-kallet ("callback-et"). Da bruker man [Response
Templates](https://docs.particle.io/reference/device-cloud/webhooks/#receiving-complex-data)
for å tolke dataen. Den ferdigtolkede dataen kommer så inn i en handler i
particle-koden. 

```json
{
    "url": "https://api.entur.io/journey-planner/v2/graphql",
    "event": "transport_event",
    "json": {
        "query": "{trip(dateTime:\"{{arrive_by}}\",from: {place: \"NSR:StopPlace:SOME_EXAMPLE_PLACE\"}, to: {place: \"NSR:StopPlace:OTHER_EXAMPLE_PLACE\"}, arriveBy:true ) {tripPatterns {startTime}}}"
    },
    "requestType": "POST",
    "responseTopic": "transport_response",
    "responseTemplate": "{{{data.trip.tripPatterns.0.startTime}}}"
}
```

Eksempelet over viser en forenklet utgave av den faktiske entur-webhooken. 
Her spesifiseres URL-en som skal kalles, og hva slags data som skal sendes med.
`{{arrive_by}}` er et eksempel på Variable Substitution, og henter data fra 
`publish`-dataen, som bør se ut omtrent som dette: 

```c
String data = String::format("{ \"arrive_by\": \"%s\" }", arrive_by_iso.c_str());
Particle.publish("transport_event", data, PRIVATE);
```

Webhooken har også definert en `resposneTopic`, som gjør at vi kan få tak i
responsdata med kode omtrent som denne: 

```c
void entur_api_handler(const char *event, const char *data)
{
    extract_from_iso(String(data));
    add_extra_time();
}

//.. senere 
Particle.subscribe("transport_response", entur_api_handler, MY_DEVICES);
```

Fordi `respnseTemplate` også er definert, vil dataen som `entur_api_handler` får
inn være hentet ut fra responsobjektet som Entur returnerer. 

Om restriksjoner med gratis-domene i mailgun TODO 
om nøkler TODO
## TODO Argumenter emer for Nytte- og underholdningsverdi

## Tanker om kode
Da jeg begynte å kode, brukte jeg en `.ino`-fil, slik som vi har gjort i
undervisningen. Jeg skjønte fort at dette kom til å bli veldig upraktisk etter
hvert som programmet vokste. Av den grunn gikk jeg over til `cpp`-filer. 
Jeg hadde ikke skrevet `C++` før jeg startet på dette prosjektet. Derimot har
jeg hatt undervisning i `C` dette semesteret. Jeg bestemte meg derfor for å
holde meg ganske nærme `C`, og holde meg unna klasser og andre `C++`-spesifikke
ting. Håpet var å unngå for mange nybeginnerfeil.

### Hovedfil
Jeg har forsøkt å holde [hovedfilen](particle/src/main.cpp) så oversiktlig som
mulig. Jeg har ønsket at logikk og "det som faktis skjer" skal ligge et annet
sted, men at man allikevel skal kunne få en grei forventning av hva programmet
gjør kun ved å se på `setup` og `loop`-funksjonene.

Funksjoner som klargjør noe (og typisk kjører i `setup`) har "setup" som prefiks
i navnet sitt. De tingene som sjekkes hver loop (sensorer o.l) gjøres i
funksjoner som er ment å beskrive handlingen så godt som mulig. Oppdatering av
skjerm diskuteres under [rendring](#rendring). 

### Rendring
Noe av det første jeg laget var støtte for å tegne data til TFT-skjermen. Dette
har jeg etter hvert begynt å se på som et lite "mini-rammeverk". Koden min
støtter rendring av "Layouts"(`Layout[]`). Et Layout inneholder "Elements"
(`Element[]`), som består av tekstbiter og forhåndsdefinerte posisjoner som de
kan vises på. 

```c
void updated_clock_elements(Element elements[MAX_ELEMENT_COUNT])
{
    String time = Time.format("%H:%M");
    String date = Time.format("%a:%b");

    elements[0] = {time, CENTER};
    elements[1] = {date, BOTTOM_RIGHT_CORNER}; 
}

Layout get_clock_layout(Screen * screen)
{
    return {
        .screen = screen,
        .element_count = element_count,
        .updated_elements = updated_clock_elements,
        .update_frequency = 60000, //i.e. every minute
    };
}
```

Utdraget ovenfra er hentet fra [koden for klokkeskjermen](particle/src/layout/clock/clock.cpp). Layoutet har en funksjonspeker som
oppdaterer elementene, og et tall (her 60000) som bestemmer hvor lang tid det
skal gå mellom hver oppdatering av skjermen. Forhåndsbestemt
oppdateringsfrekvens gjør at jeg kan bestemme hvor ofte et layout skal
oppdateres avhengig av hva som vises. På den måten sparer jeg ressurser, og jeg
unngår hyppig blinking på skjermen. Klokken oppdateres en gang i minuttet, fordi
det kun er da det vil være ny, nyttig informasjon til brukeren. 

Når alle layouts følger dette formatet, kan jeg bruke [samme kode](particle/src/render/render.cpp) for å rendre
alt som skal på skjermen i hele oppgaven: 

```c
void render_current_layout(LayoutState * layout_state_pointer)
{
    Layout layout = layout_state_pointer->layouts[layout_state_pointer->current_layout_index];
    Screen * screen_pointer = layout.screen;

    Element elements[layout.element_count]; 
    layout.updated_elements(elements);

    clear_screen(screen_pointer); 

    for (int i = 0; i < layout.element_count; i++)
    {
        Element element = elements[i];         
        render_element(screen_pointer, element.text, element.position);
    }
}
```



### Reflekter rundt valg av bibliotek
Jeg har brukt [Adafruit_ST7735](https://github.com/menan/adafruit_st7735) for å
skrive til skjermen. Dette er det eneste eksterne biblioteket jeg bruker. Dette
er en port av [Adafruit sitt
originalbibliotek](https://github.com/adafruit/Adafruit-ST7735-Library), til
Particle. Originalbiblioteket ble senest oppdatert for et par måneder siden, og
ser ut til å være ganske aktivt vedlikeholdt. Porten som jeg bruker har
dessverre ikke samme aktivitetsnivå. Det har allikevel fungert fint for meg, og
siden det er en port, kan dokumenatsjonen til originalbiblioteket gjenbrukes. 

Dessuten ligger biblioteket på Particle sin egen
["awesome"-liste](https://github.com/particle-iot/awesome-particle). Det har jeg
tatt som et tegn på at de anbefaler- og bruker det selv. 

## Mulige utvidelser

TODO: skriv om mulige utvidelser/forbedringer (men bruk ordet utvidelser)

## Komponenter fra settet 
* Particle Photon
* Breadboard
* Fargeskjerm
* Flammesensor
* Vannsensor
* LM35 temperatursensor
* Fargeskjerm
* 2x LED rød
* 1x LED grønn
* 3x 220 resistor 
* 2x push-button (6x6mm)
* Koblingskabler 

## Om film
Jeg har lagt ved flere små filmer. 
Jeg har delt opp filmene fordi jeg tror det gjør det lettere å vise dingsen. 
Det er flere funksjoner her, og selv om jeg mener at alle funksjonene har nytte- 
og/eller underholdningsverdi på en alarmklokke, tror jeg allikevel det hadde blitt 
litt rotete å stappe alt sammen inn i samme video. 
### Videoer jeg har lagt ved:
* [Alarm](./media/alarm.mp4) viser hovedfunksjonaliteten. Dingsen konfigureres
gjennom webgrensesnittet. Den kommuniserer automatisk med Entur og finner neste
alarmtidspunkt basert på dataen den blir konfigurert med. Alarmen ringer også i
videoen. Ringelyden (til slutt) er ikke pen for ørene - man skal jo
tross alt våkne skikkelig av den. 
MERK: det er en liten unøyaktighet i videoen: GUI-et viser alarmtidspunktet som
konfigurert fra start av, til høyre. Denne verdien henger igjen fra tidligere
testing.
* [Julemodus](./media/christmas.MOV)
* Video om skadedetektering, for [ild](./media/fire.MOV) og [vann](./media/water.MOV)
* [Video om valgfri melding](./media/message.MOV)
* Demo av [temperatur](./media/temperature.MOV) viser lokalt målt temperatur og
den fra egenvalgt by, samt endring av valgt by gjennom GUI
* En kort [video](./media/navigation.MOV) som viser navigering.

## Koblingsskjema
Det er noen avvik i koblingsskjemaet: 
* Skjermen er ikke den samme, men en som ligner, med PIN-navn på et notat. 
* Flammesensoren representeres med en grå, infrarød LED

Jeg har lagt ved skjemaet som `.fzz` og `.png`. 

![Bilde av skjemaet](./media/sketch.png)

## Kilder 

* JEg har tenkta tdette er iot, og at mye derfor bør skje over nett. 



TODO: fjern under
# Dokumentasjon 

* skriv om fronted -> setup med .env
* forskjellige maater aa endre tidspunkt paa (iso/individuel)
* Koblet opp mye mot cloud (eksponert vars osv.) for aa kunne utvide mer senere 
* flammemail referanse til IT project  
* legg til screenshot av webhook-config (sladd nøkler)
* Nasjonalt stoppestedsregister (NSR) -> https://stoppested.entur.org/?stopPlaceId=NSR:StopPlace:13825, logg inn med guest/guest
* om nøkler
* om regelmessig oppdatering av alarm

* Oversikt over komponenter 
* Skrive hvilke komponenter 
* Reflekter rundt valg av bibliotek 
* Hvordan oppgaven ble angrepet 
* Beskriv hva du har tenkt med koden (ikke hvordan den fungerer) 
* Sannsynliggjøre at du har forstått oppgaven 
* Sjekk en v første slides fra iot-forelesning

* koplingsskjema - Fritzing 
* bruke LED-driver 
* film av prosjekt 
* Forklaring i dokumentasjon
* __veldig viktig med ekstra features__ 
* ryddig kode 


- God dokumentasjon 
- Unoedvendige ting som er morsomme 
- leking 
- god kode
- ikke hardkod verdier 
- gjør noe ekstra -> lite til for at det er bedre 
- Bygg inn noe analogt 


Krav: 
* Løser oppgaven: C 
* Mer enn nødvendig, ekstra funksjoner: B
* Mange forskjellige, morsomme ting som passer produktet: A  

Et mål å vise det man har lært 

Dokumentasjon: 
Hvis man ikke kan forklare noe, betyr det at man ikke kan det. 
Det er et utgangspunkt at den som leser er en ekstern sensor som kan _litt_ Arduino. Vedkomne skal forstå hvordan ting fungerer. Prinsipper. 
* Forklar spesielle ting man må gjøre 
* Begrunn valg man tar 
* Kode bør i utgangspunktet forklare seg selv 
