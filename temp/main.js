
function makeHtmlSelectOptionString(value, displayString, selected){
    var str, selectStr='';
    if (selected !== undefined && selected === true) {
        selectStr = ' selected="selected"';
    }
    
    str = '<option value="' + value + '"' + selectStr + '>' + displayString + '</option>';
    return str;

}

function makeHtmlSelectString(pin, mode){
	var str ='<select id="m' + pin + '" class="form-control">';
    str += makeHtmlSelectOptionString(0, "INPUT_ANALOG", mode === 0);
    str += makeHtmlSelectOptionString(1, "INPUT_DIGITAL", mode === 1);
    str += makeHtmlSelectOptionString(2, "OUTPUT_ANALOG", mode === 2);
    str += makeHtmlSelectOptionString(3, "OUTPUT_DIGITAL", mode === 3);
    str +='</select>';
	return str;
}

function setPinValues(pins){
	
	var modeStr;
	var $elm = $('#table-pins tbody');
	var row;
	$('#pin-count').text(pins.length);
	for(var i = 0; i < pins.length; i++){
		modeStr = makeHtmlSelectString(pins[i].pin, pins[i].m);
		row = '<tr>'+
			'<td>'+pins[i].name+'</td>'  +
			'<td>'+pins[i].pin+'</td>'  +
			'<td id="val'+ pins[i].pin +'">'+pins[i].val+'</td>'  +
			'<td>'+modeStr+'</td></tr>';
		$elm.append(row);
	}
}



function getPinsFromTable(){
    var pins= [];
    var item;
    var table = document.getElementById("table-pins");
    for (var i = 2; i < table.rows.length -1 ;  i++) {
        var row = table.rows[i]
        item = {};
        item.name = row.cells[0].textContent;
        item.pin =  Number(row.cells[1].textContent);
        item.val =  Number(row.cells[2].textContent);
        e =document.getElementById("m"+item.pin);
        item.m = Number(e.options[e.selectedIndex].value);
        pins.push(item);
    //iterate through rows
    //rows would be accessed using the "row" variable assigned in the for loop
    /*for (var j = 0, col; col = row.cells[j]; j++) {
        //iterate through columns
        //columns would be accessed using the "col" variable assigned in the for loop
    }*/  
    }
    //pins.push({name: 'D0', pin:0, val: 10, m : 0 });
    return pins;
}

$(document).ready(function(){
    console.log('document is ready!');

    $('#change-me').text("You have been warnedx!");
    console.log('stuff');
    console.log('prup');
    var pins =        [
        {name: 'D0', pin:0, val: 10, m : 0 },
        {name: 'D1', pin:1, val: 11, m : 1 },
        {name: 'D2', pin:2, val: 12, m : 2 },
        {name: 'D3', pin:3, val: 13, m : 3 },
        {name: 'D4', pin:4, val: 14, m : 2 },
        {name: 'D5', pin:5, val: 15, m : 2 },
        {name: 'D6', pin:6, val: 16, m : 2 },
        {name: 'D7', pin:7, val: 17, m : 2 },
        {name: 'D8', pin:8, val: 18, m : 2 },
        {name: 'D9', pin:9, val: 19, m : 2 },
        {name: 'D10', pin:10, val: 20, m : 2 },
        {name: 'D11', pin:11, val: 21, m : 2 },
       ] 
    setPinValues(pins);
    var data = getPinsFromTable();
    console.log(data);
});

