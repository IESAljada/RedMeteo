# Software

El programa fué modificado tras comprobar que daba error, no subía a ThinkSpeak las lecturas y se bloqueaba (sin motivo aparente). 
Comprobé que si lo hacía directo con una solicitud POST de HTTP las cosas funcionaban mejor.

Hay un archivo llamado **secrets.h** donde hay que introducir unos códigos:
Constante|Valor
---------|-----
SECRET_CH_ID | Tu número de canal de ThinkSpeak
SECRET_WRITE_APIKEY | Tu clave para escribir (write API Key)
  

Y en el programa principal hay que cambiar la dirección IP si se desea que tenga una dirección fija en la red local el arduino uno.
    
    // Set the static IP address to use if the DHCP fails to assign
    IPAddress ip( 0, 0, 0, 0);
    IPAddress myDns( 0, 0, 0, 0);

## Software auxiliar

En la carpeta **pruebas** hay programas para comprobar y ajustar el funcionamiento de los sensores:
* prueba_anemometro.ino
* prueba_dht11.ino
* prueba_pluviometro.ino



