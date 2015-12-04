var Images = [
  "1.png",
  "2.png",
  "3.png",
  "4.png",
  "5.png",
  "6.png",
  "7.png",
  "8.png",
  "9.png",
  "10.png",
];

var BoxOpen = "";
var ImgOpen = "";
var Counter = 0;
var Len = Images.length;

function Rand(MaxValue, MinValue) {
  return Math.round(Math.random() * (MaxValue - MinValue) + MinValue);
}

function ShuffleImages() {
  var ImgThis = $("#box div:first-child");
  var ImgArr = new Array();

  var i = 0;
  while (ImgThis.attr("id") != undefined) {
    ImgArr[i] = $("#" + ImgThis.attr("id") + " img").attr("src");
    ImgThis = ImgThis.next();
    i++;
  }

  ImgThis = $("#box div:first-child");

  while (ImgArr != "") {
    var r = Rand(ImgArr.length - 1, 0);
    $("#" + ImgThis.attr("id") + " img").attr("src", ImgArr[r]);
    ImgArr.splice(r, 1);
    ImgThis = ImgThis.next();
  }
}

function Open() {
  var Id = $(this).attr("id");

  if ($("#" + Id + " img").is(":hidden")) {
    $("#" + Id + " img").fadeIn(500);
    if (ImgOpen == "") {
      ImgOpen = $("#" + Id + " img").attr("src");
      BoxOpen = Id;
      $("#box div").bind("click", Open);
    } else {
      if (ImgOpen == $("#" + Id + " img").attr("src")) {
        setTimeout(function () {
          $("#" + Id + " img").parent().css("visibility", "hidden");
          $("#" + BoxOpen + " img").parent().css("visibility", "hidden");
          Counter++;
          BoxOpen = "";
          ImgOpen = "";
          if (Counter == Len) {
            alert("Wygrałeś!");
          }
        }, 800);

      } else {
        setTimeout(function () {
          $("#" + Id + " img").fadeOut(150);
          $("#" + BoxOpen + " img").fadeOut(150);
          BoxOpen = "";
          ImgOpen = "";
        }, 600);
      }
      setTimeout(function () {
        $("#box div").bind("click", Open)
      }, 250);
    }
  }

}

$(function () {

  for (var y = 1; y < 3; y++) {
    $.each(Images, function (i, val) {
      $("#box").append("<div id=card" + y + "_" + i + "><img src=" + val + " />");
    });
  }
  $("#box div").click(Open);
  ShuffleImages();
});	