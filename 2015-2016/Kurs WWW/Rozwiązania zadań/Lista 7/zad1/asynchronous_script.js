function get_details(){
    var city_id=document.getElementById('city').value;
    var imgg=xml_str.getElementsByTagName("image");
    var opis=xml_str.getElementsByTagName("description");
    kodhtml='';
    for(i=0;i<nejm.length;i++){
        if(ajdi[i].childNodes[0].nodeValue == city_id) {
            kodhtml += '<br />\n' +
                '<img src="' + imgg[i].childNodes[0].nodeValue + '">';
            kodhtml += '<br />\n<div>' + opis[i].childNodes[0].nodeValue + '</div>';
        }
    }

    document.getElementById('disp').innerHTML=kodhtml;
}


if(window.XMLHttpRequest)
    my_xml=new XMLHttpRequest();

my_xml.open("GET",'./cities3.xml',false);
my_xml.send();
xml_str=my_xml.responseXML;

var nejm=xml_str.getElementsByTagName("name");
var ajdi=xml_str.getElementsByTagName("id");
var str="<select id='city' onchange=get_details()>";
str += "<option value='0'>Wybierz miasto</option>";
for(i=0;i<nejm.length;i++){
    str +='<option value=' + ajdi[i].childNodes[0].nodeValue + '>' + nejm[i].childNodes[0].nodeValue + '</option>';
}
str +='</select>';
document.write(str);
