# NXT and Raspberry Pi Communications

http://lejos-osek.sourceforge.net/ecrobot_c_api.htm

`void ecrobot_init_usb(void)`

`ecrobot_read_usb` læser fra usb, med længde fixed

`ecrobot_send_usb` sender fixed length igen

Vi skal nok have et låst format, på length, fordi det er nemmest at læse således. USB virker som den mest solide løsning ift. delays, eller usikkerheden i bluetooth, selvom afstanden er fixed og kort.

Hvis vi laver fixed length communication, med fx length 16; låst format. Første 4 er `signed int` for `x`; næste 4 er `y` (korrigering) og sidste er noget 3, fx timestamp for data. Vi skal bruge sync over USB og initialize til at synce en "starttime", ala NTP-stilen. Det er et problem vi skal løse..

Problem 2 er at

`U8 ecrobot_process1ms_usb(void)`

USB process handler to establish a connection with a host. This function must be invoked every 1msec. (i.e. in a loop with 1msec wait, OSEK/JSP 1msec peiodical Task)

skal kaldes hvert 1ms; Jeg ved ikke hvad konsekvensen er af dette på en Pi, men mon ikke den kan "følge med", alt efter hvad modsvaret skal være, skal vi dog være klar på dette i den anden ende.


Nye kort til backlog:
 * Raspberry Pi USB Analysis; Delay Handling?
 * NXT Pi Analysis; Delay Handling?
 * Opfind et dataformat, der kan dække vores "krav" ift x, y og tidssync/delay håndtering.
 * Overordnet NTP Time Sync problemet. Hvordan synkroniserer vi ure ift. at kunne "se om data er gyldigt" når det kommer fra Pi?