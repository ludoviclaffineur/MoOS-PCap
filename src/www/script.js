$(document).ready(function(){
        $("#demosMenu").change(function(){
                window.location.href = $(this).find("option:selected").attr("id") + '.html';
        });
        //setGrid();
        $(".sidebar").hide();
        var $body = $('#drawingGrid');
        $body.mousedown(function (evt) {
                selectedWeight = selectWeight(evt);
                yInit = evt.offsetY;
                if(selectedWeight){
                        oldWeight = selectedWeight["weight"] ;
                }

                if(typeof selectedWeight !== 'undefined'){
                        $body.mousemove(function handler(evt2) {
                                if (evt.type === 'mouseup') {
                                        selectedWeight = null;

                                } else {
                                        var draggedWeight = parseFloat(oldWeight) + (yInit - evt2.offsetY).toPrecision(3)/20.0;
                                        if (draggedWeight>1){
                                                draggedWeight = 1;
                                        }
                                        else if(draggedWeight< -1){
                                                draggedWeight = -1;
                                        }
                                        selectedWeight["weight"]= draggedWeight;
                                        sendWeight(selectedWeight);
                                        redraw();
                                }
                                //$body.off('mouseup mousemove', handler);

                        });

                }
                else{
                        var selectedOutput = getOutput(evt);
                        showOutput(selectedOutput);
                        $(".sidebar").bPopup();
                }


        })
        .mouseup( function(){
                $body.unbind("mousemove");;
        });
});

wsUri = "ws://127.0.0.1:9002"; var output;
obj = new Object();
colorLine = "#ccc" /*"#7E3027"*/
colorPositive = "#19B2A5"
colorNegative = "#FC5F4D"
//decalageX = 200;
decalageY = 100;
sizeGrid = 43;

function trigGrid(){

        var text = '{"action": "trig"}';
        doSend(text);
}


function  showOutput(selectedOutput){
        var section0 = $(".sidebar").find("label");
        var label =  section0.eq(0);
        var keys = Object.keys(selectedOutput);
        var i = 0;
        $( ".sidebar" ).empty();
        var identifierO;
        if(i<keys.length){
                for(var j =i;j<keys.length;j++){
                        if(keys[j] !== "Identifier" && keys[j] !== "OutputType"){
                                $(".sidebar").append(
                                        $("<p>").prop("class", "textArea").append(
                                                $("<label>").append(
                                                      keys[j]
                                                )
                                        )
                                ).append(
                                        $("<p>").prop("class", "textArea").append(
                                                $("<input>").prop("type","text").prop("id",keys[j]).prop("value", selectedOutput[keys[j]])
                                        )
                                )
                        }
                        else if (keys[j] == "Identifier"){
                                identifierO = selectedOutput[keys[j]];
                        }
                        else if (keys[j] == "OutputType"){
                                currentOutputType = selectedOutput[keys[j]];
                        }

                }
                $(".sidebar").append(
                        $("<p>").prop("class","submit").append(
                                $("<input>").prop("type", "submit").click({id: identifierO},function(evt){ setOutput(evt.data.id); return false; })
                        )
                )

        }

}

function setOutput(identifier){
       var newValuesInputs = $( ".sidebar" ).find("input");
       var text = '{"action": "setOutput",'+
       '"parameters": {"identifier": "'+identifier+'",';
       //text = text+'"OutputType": "'+currentOutputType+'",';
       for (var i = 0; i<newValuesInputs.length-1;i++){
               text = text+'"'+ newValuesInputs[i].id +'": "'+newValuesInputs[i].value+'"';
               if( i !=newValuesInputs.length-2){
                       text = text+',';
               }

       }
       text = text + "}}"
       doSend(text);
       $(".sidebar").bPopup().close();
}

function getOutput(evt){
        var output;
        for(var i = 0; i<outputs.length;i++){
                if(2+sizeGrid+decalageY+i*sizeGrid < evt.offsetY+10 &&
                   2+sizeGrid+decalageY+i*sizeGrid > evt.offsetY-10 &&
                evt.offsetX -200< inputs.length*sizeGrid+sizeGrid + 10 &&
                        evt.offsetX +10 > inputs.length*sizeGrid+sizeGrid + 10){
                                return outputs[i];
                        }
        }
}

function sendWeight(weight){
        var text = '{"action": "sendWeight",'+
           '"parameters": {"weight": "'+weight["weight"]+'",'+
                           '"inputName": "'+weight["inputName"]+'",'+
                           '"outputName": "'+weight["outputName"]+'"}}';
                           doSend(text);
}

function selectWeight(evt){
        var j = -1;
        var indexSelected = -1;
        for(var i = 0; i<weights.length;i++){
                var indexX = i - j*inputs.length;
                if(i%inputs.length == 0){
                        j++;
                        indexX = 0;
                }
                sizeGrid+sizeGrid*indexX, decalageY+ sizeGrid+sizeGrid*j
                if(evt.offsetX +15> sizeGrid+sizeGrid*indexX &&
                        evt.offsetX - 15 < sizeGrid+sizeGrid*indexX &&
                        evt.offsetY + 15 > decalageY+ sizeGrid+sizeGrid*j &&
                        evt.offsetY - 15 < decalageY+ sizeGrid+sizeGrid*j)
                        {
                                indexSelected = i;

                }
        }
        return weights[indexSelected];
}

function setGrid(params){

        outputs = Object.keys(params["outputs"]).map(function(k) { return params["outputs"][k] });
        inputs = Object.keys(params["inputs"]).map(function(k) { return params["inputs"][k] });
        weights = Object.keys(params["weights"]).map(function(k) { return params["weights"][k] });
        rowData = Object.keys(params["rowsData"]).map(function(k) { return params["rowsData"][k] });
        contextGlobal = getContextHq();
        contextGlobal.clearRect(0, 0, 800, 800);
        drawGrid(inputs.length,outputs.length);
        drawInputsLabels(inputs);
        drawOutputsLabels(outputs, inputs.length);
        drawWeigths(weights, inputs.length);
        setDescription(params['description']);
        setDropDownMenu(rowData);

        window.location.href = '#grid';
}

function setDropDownMenu(desc){
        var dropdown = $(".dropdown");
        dropdown.empty();
        for(var i=0; i<desc.length;i++){
                dropdown.append(
                        $("<li>").append(
                                $("<a>").text(desc[i]).click({id: i},function(evt){ setRow(evt.data.id); return false; })
                        )
                )
        }
}

function setRow(id){
        var text = '{"action": "setRow", "parameters": "'+id+'"}';
        var dd =  $(".wrapper-dropdown-3").blur();
        doSend(text);
        dd.blur();
}

function setDescription(desc){
        $(".grid h1").text(desc);
}

function redraw(){
        contextGlobal = getContextHq();
        contextGlobal.clearRect(0, 0, 800, 800);
        drawGrid(inputs.length,outputs.length);
        drawInputsLabels(inputs);
        drawOutputsLabels(outputs, inputs.length);
        drawWeigths(weights, inputs.length);
}

function drawInputsLabels(inputs){
        contextGlobal.font = "15px consolas";
        for(var i=0; i<inputs.length;i++){
                contextGlobal.save();
                contextGlobal.translate(sizeGrid+i*sizeGrid,decalageY-5);
                contextGlobal.rotate(-Math.PI/6.0);
                contextGlobal.fillText(inputs[i][i],0,0);
                contextGlobal.restore();
        }
}

function drawWeigths(weights, inputsLength){
        var j = -1;
        for(var  i=0 ; i<weights.length ; i++){
                var indexX = i - j*inputsLength;
                if(i%inputsLength == 0){
                        j++;
                        indexX = 0;
                }

                contextGlobal.beginPath();
                if(weights[i]["weight"] >=0){
                        contextGlobal.fillStyle = colorPositive;
                        contextGlobal.arc(sizeGrid+sizeGrid*indexX, decalageY+ sizeGrid+sizeGrid*j, 5+ 15*weights[i]["weight"], 0, Math.PI*2, true);
                }
                else{
                        contextGlobal.fillStyle = colorNegative;
                        contextGlobal.arc(sizeGrid+sizeGrid*indexX, decalageY+ sizeGrid+sizeGrid*j, 5+ 15*(-weights[i]["weight"]), 0, Math.PI*2, true);
                }

                contextGlobal.closePath();
                contextGlobal.fill();
        }

}

function drawOutputsLabels(outputs,inputSize){
        for(var i=0; i<outputs.length;i++){
                contextGlobal.fillText(outputs[i]["Name"],inputSize*sizeGrid+sizeGrid + 10, 2+sizeGrid+decalageY+i*sizeGrid);
        }
}

function drawGrid( inputs, outputs ){

        contextGlobal.lineWidth = 3;
        for (var i= 0; i < inputs; i ++) {
                  contextGlobal.moveTo(sizeGrid+i*sizeGrid, decalageY);
                  contextGlobal.lineTo(sizeGrid+i*sizeGrid, decalageY+outputs*sizeGrid+sizeGrid);
        }
        for (var i= 0; i < outputs; i ++) {
          contextGlobal.moveTo(0, decalageY+sizeGrid+i*sizeGrid);
          contextGlobal.lineTo(inputs*sizeGrid+sizeGrid, decalageY + sizeGrid+ i*sizeGrid);
        }
        contextGlobal.strokeStyle = colorLine;
        contextGlobal.stroke();

}

function getContextHq(){
        var PIXEL_RATIO = (function () {
                var ctx = $('#drawingGrid').get(0).getContext("2d");
                dpr = window.devicePixelRatio || 1,
                bsr = ctx.webkitBackingStorePixelRatio ||
                      ctx.mozBackingStorePixelRatio ||
                      ctx.msBackingStorePixelRatio ||
                      ctx.oBackingStorePixelRatio ||
                      ctx.backingStorePixelRatio || 1;

            return dpr / bsr;
        })();


        createHiDPICanvas = function(w, h, ratio) {
            if (!ratio) { ratio = PIXEL_RATIO; }
            var can = $('#drawingGrid').get(0);
            can.width = w * ratio;
            can.height = h * ratio;
            can.style.width = w + "px";
            can.style.height = h + "px";
            can.getContext("2d").setTransform(ratio, 0, 0, ratio, 0, 0);
            return can;
        }

        //Create canvas with the device resolution.
        var myCanvas = createHiDPICanvas(800, 800);

        //Create canvas with a custom resolution.
        return myCanvas.getContext("2d");

}


function init() {

        output = document.getElementById("output");
        window.onbeforeunload = function() {
            websocket.onclose = function () {}; // disable onclose handler first
            websocket.close()
        };

        testWebSocket();
}

function testWebSocket() {
        websocket = new WebSocket(wsUri);
        websocket.onopen = function(evt) { onOpen(evt) };
        websocket.onclose = function(evt) { onClose(evt) };
        websocket.onmessage = function(evt) { onMessage(evt) };
        websocket.onerror = function(evt) { onError(evt) };
}

function onOpen(evt) {
        //writeToScreen("CONNECTED");
        $("input[id*='yes']").prop("checked",true);
        var text = '{"action":  "init"}';
        doSend(text);
}
function onClose(evt) {
        //writeToScreen("DISCONNECTED");
        $("input[id*='no']").prop("checked",true);
}
function onMessage(evt) {
        //var ctx = document.getElementById("canvas").getContext("2d");

        var Json_Tree_Object = JSON.parse(evt.data);
        if(Json_Tree_Object["action"] == "capture_device_list"){
                setCatpureDeviceList(Json_Tree_Object["parameters"]);
        }
        else  if(Json_Tree_Object["action"] == "setConfiguration"){
                setConfigurationList(Json_Tree_Object["parameters"]);
        }
        else  if(Json_Tree_Object["action"] == "set_outputs_list"){
                setOutputsList(Json_Tree_Object["parameters"]);
        }
        else  if(Json_Tree_Object["action"] == "stopConnection"){
                websocket.onclose = function () {}; // disable onclose handler first
                websocket.close();
        }
        else  if(Json_Tree_Object["action"] == "setGrid"){
                setGrid(Json_Tree_Object["parameters"]);
        }
        else  if(Json_Tree_Object["action"] == "setOutputConfig"){
                setOutputConfig(Json_Tree_Object["parameters"]);
        }
        else  if(Json_Tree_Object["action"] == "setDescription"){
                setDescription(Json_Tree_Object["parameters"]);
        }
        // lineChartData.datasets[0].data =Object.keys(obj).map(function(k) { return obj[k] });

}

function setOutputConfig(CPList){
        var arrayWork = Object.keys(CPList).map(function(k) { return CPList[k] });

        var section0 = $(".OutputsConfiguration").find("li a");
        var uls = $(".OutputsConfiguration");
        var lis =  section0.eq(0);
        lis.text(arrayWork[0]);
        lis.click(function(){ setMidiPort(0); return false;  });
        var id = 1;
        for (var  i = 1 ; i< arrayWork.length; i++){
                uls.append(
                        $('<li>').append(
                                $('<a>').attr('href','#grid').append(arrayWork[i])
                        )
                )
                section0 = $(".OutputsConfiguration").find("li a");
                section0.eq(i).click({id: i},function(evt){ setMidiPort(evt.data.id); return false; })

        }
        window.location.href = '#outputsConfiguration';
}

function setMidiPort(identifier){
     var text = '{"action": "setMidiPort",'+
        '"parameters": {"id": "'+identifier+'"}}';
        doSend(text);
}

function setOutputsList(CPList){
        var arrayWork = Object.keys(CPList).map(function(k) { return CPList[k] });

        var section0 = $(".Outputs").find("li a");
        var uls = $(".Outputs");
        var lis =  section0.eq(0);
        lis.text(arrayWork[0]);
        lis.click(function(){ setDefaultOutput(0); return false;  });
        var id = 1;
        for (var  i = 1 ; i< arrayWork.length; i++){
                uls.append(
                        $('<li>').append(
                                $('<a>').attr('href','#grid').append(arrayWork[i])
                        )
                )
                section0 = $(".Outputs").find("li a");
                section0.eq(i).click({id: i},function(evt){ setDefaultOutput(evt.data.id); return false; })

        }
        window.location.href = '#outputs';

}


function setConfigurationList(CPList){


        var arrayWork = Object.keys(CPList).map(function(k) { return CPList[k] });

        var section0 = $(".Configuration").find("li a");
        var uls = $(".Configuration");
        var lis =  section0.eq(0);
        lis.text(arrayWork[0]);
        lis.click(function(){ setConfigDevice(0); return false; });
        var id = 1;
        for (var  i = 1 ; i< arrayWork.length; i++){
                uls.append(
                        $('<li>').append(
                                $('<a>').attr('href','#grid').append(arrayWork[i])
                        )
                )
                section0 = $(".Configuration").find("li a");
                section0.eq(i).click({id: i},function(evt){ setConfigDevice(evt.data.id); return false; })

        }
        window.location.href = '#configuration';


}

function setDefaultOutput(id){
        var text = '{"action": "setDefaultOutput",'+
           '"parameters": {"id": "'+id+'"}}';
           doSend(text);
}

function setConfigDevice(id){
var text = '{"action": "setConfigurationPcap",'+
           '"parameters": {"id": "'+id+'"}}';
doSend(text);

}

function setCatpureDeviceList(CPList){
        var arrayWork =Object.keys(CPList).map(function(k) { return CPList[k] });
        var section0 = $(".CaptureList").find("li a");
        var uls = $(".CaptureList");
        var lis =  section0.eq(0);
        lis.text(arrayWork[0]);
        lis.click(function(){ setCaptureDevice(0); return false; });
        var id = 1;
        for (var  i = 1 ; i< arrayWork.length; i++){
                uls.append(
                        $('<li>').append(
                                $('<a>').attr('href','#configuration').append(arrayWork[i])
                        )
                )
                section0 = $(".CaptureList").find("li a");
                section0.eq(i).click({id: i},function(evt){ setCaptureDevice(evt.data.id); return false; })
        }
}


function onError(evt) {
        writeToScreen('<span style="color: red;">ERROR:</span> ' + evt.data);
}
function doSend(message) {
        //writeToScreen("SENT: " + message);
        websocket.send(message);
}
function writeToScreen(message) {
        var pre = document.createElement("p");
        pre.style.wordWrap = "break-word";
        pre.innerHTML = message; output.appendChild(pre);
}


function setCaptureDevice(id){
        var text = '{"action": "setCaptureDevice",'+
                   '"parameters": {"id": "'+id+'"}}';
        doSend(text);
        //window.location.href = '#configuration'
}

function getSavedFiles(){
var text = '{"action": "getSavedFiles",'+
           '"parameters": ""}';
doSend(text);
}



