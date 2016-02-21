var entryCounter = 0;
var markerList = [];

var informationWindow = new google.maps.InfoWindow({
  content: 'To tu!'
});

function initializeGoogleMaps() {

  var styles = [
    {
      featureType: 'water',
      elementType: 'geometry.fill',
      stylers: [
        {color: '#adc9b8'}
      ]
    }, {
      featureType: 'landscape.natural',
      elementType: 'all',
      stylers: [
        {hue: '#809f80'},
        {lightness: -35}
      ]
    }
  ];

  var options = {
    mapTypeControlOptions: {
      mapTypeIds: ['Styled']
    },
    center: new google.maps.LatLng(-7.245217594087794, 112.74455556869509),
    zoom: 16,
    disableDefaultUI: true,
    mapTypeId: 'Styled'
  };

  map = new google.maps.Map(document.getElementById('map'), options);
  var styledMapType = new google.maps.StyledMapType(styles, {name: 'Styled'});
  map.mapTypes.set('Styled', styledMapType);


  google.maps.event.addListener(map, "dblclick", function (event) {
    var latitude = event.latLng.lat();
    var longitude = event.latLng.lng();

    addMaker(latitude, longitude);

    var marker = new google.maps.Marker({
      position: {lat: latitude, lng: longitude},
      map: map
    });

    markerList.push(marker);

  });

}

function addMaker(latitude, longitude) {

  var entryHTML = '<div id="' + (entryCounter) + '" class="entry">' +
    '<div>' + entryCounter + '. latitude: ' + latitude + ' longitude: ' + longitude + '</div>' +
    '<div> <button onclick="showMarker(this)">Pokaż</button> ' +
    '<button onclick="deleteMarker(this)">Usuń</button> ' +
    '</div> </div>';

  document.getElementById('latLongList').innerHTML += entryHTML;
  entryCounter++;
}

function showMarker(marker) {
  var id = marker.parentNode.parentNode.getAttribute('id');
  informationWindow.open(map, markerList[Number(id)]);
}

function deleteMarker(marker) {
  var id = marker.parentNode.parentNode.getAttribute('id');
  markerList[Number(id)].setMap(null);  // Jak chcemy usuwac cos z mapy to musimy ustawic to na null
  var parent = marker.parentNode.parentNode;
  parent.parentNode.removeChild(parent);
}