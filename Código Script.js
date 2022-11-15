/*function doPost(e) { //V1 estable (solo envia datos a la ultima fila de todo el documento)
   var ss1 = SpreadsheetApp.getActiveSpreadsheet();
   var sheet = ss1.getSheets()[0];

   var fechaHora = Utilities.formatDate(new Date(), "GMT-3", "yyyy-MM-dd HH:mm:ss");
   valor = String(e.parameters.data);
   sheet.appendRow([fechaHora,valor]);
   
   return ContentService.createTextOutput("Completo");
}*/

/*V2 estable */

function doPost(e) { //Realizaa mapeo del documento y selecciona la ulltima fila de la columna A
  var ss1 = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss1.getSheets()[0];

  var fechaHora = Utilities.formatDate(new Date(), "GMT-5", "yyyy-MM-dd HH:mm:ss");
  valor = String(e.parameters.data); //Variable que se envia desde esp8266
  //valor = 14143;
  valor2 = parseInt(valor);
  //sheet.appendRow([fechaHora, valor2]);

  var values = [[fechaHora, valor2]];

  /*-------------- */
  var columna = "A";
  var ss = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var maximoFilas = ss.getMaxRows();

  var valores = ss.getRange(columna + "1:" + columna + maximoFilas).getValues();

  for (; valores[maximoFilas - 1] == "" && maximoFilas > 0; maximoFilas--) { }

  //Logger.log(maximoFilas);
  /*-------------- */

  maximoFilasT = maximoFilas + 1;
  var destRange = sheet.getRange("A" + maximoFilasT + ":" + "B" + maximoFilasT).setValues(values);

  return ContentService.createTextOutput("Completo");
}

function doGet(e){
  var ss = SpreadsheetApp.openById('1FNZapy5yeC-On-YrMA-5TgRumcWGqSi5FQRD4gPg_TU');
  var sheet = ss.getSheetByName('Asistencia');
/*-------------- *///Buscar ultima fila
  var columna = "A";
  var ss = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var maximoFilas = ss.getMaxRows();

  var valores = ss.getRange(columna + "1:" + columna + maximoFilas).getValues();

  for (; valores[maximoFilas - 1] == "" && maximoFilas > 0; maximoFilas--) { }

  //Logger.log(maximoFilas);
  /*-------------- */

 /*-------------- *///obtener último nombre y hora
  var dato = ss.getRange("C" + maximoFilas).getValue(); //Enviar a esp8266 (Nombre) Variable dato
  //Logger.log(dato);

  var dato2 = ss.getRange("A" + maximoFilas).getValue();
  //Logger.log(dato2);
  horaStr = String(dato2);
  //Logger.log(horaStr);
  //var dato2 = "Wed Aug 10 2022 08:59:50 GMT-0500";
  let [dia, mes, dia2, anio, hora, zona] = horaStr.split(' ');
  var valHora = hora;
  //Logger.log(hora);
  valHora2 = hora.split(":", 2);
  //Logger.log(valHora2);
  let union = valHora2.join(':'); //Enviar a esp8266 (Hora) Variable union
  //Logger.log(union);
  /*-------------- */
  var union_Data = union +"-"+ dato;
  var read = e.parameter.read;

  if (read !== undefined){
    //return ContentService.createTextOutput(sheet.getRange('C'+maximoFilas).getValue());
    return ContentService.createTextOutput(union_Data);
  }
}