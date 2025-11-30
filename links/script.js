function display(obj) {
  var content = obj.nextElementSibling;
  if (content.style.display === "block") {
    content.style.display = "none";
  } else {
    content.style.display = "block";
  }
}
function link_search() {
  var input = document.getElementById("searchBox");
  var filter = input.value.toUpperCase();
  links = document.getElementsByTagName("li");
  for (var i = 0; i < links.length; i++) {
    var content = links[i].innerHTML.toUpperCase();
    if (content.indexOf(filter) != -1) {
      links[i].style.display = "";
    } else {
      links[i].style.display = "none";
    }
  }
}

function log_search() {
  var input = document.getElementById("searchBox");
  var filter = input.value.toUpperCase();
  details = document.getElementsByTagName("details");
  for (var i = 0; i < details.length; i++) {
    var detail = details[i].innerHTML.toUpperCase();
    if (detail.indexOf(filter) != -1) {
      details[i].style.display = "";
    } else {
      details[i].style.display = "none";
    }
  }
}

function onHover() {
  let name = event.target.alt;
  let path = "/links/images/" + name + ".gif";
  event.target.src = path;
}

function onOut() {
  let name = event.target.alt;
  let path = "/links/images/" + name + ".png";
  event.target.src = path;
}

function showLogCount() {
  let elem = document.getElementById("logsList");
  if (typeof elem !== "undefined" && elem !== null) {
    let count = elem.childElementCount;
    let countElem = document.getElementById("logsCount");
    if (
      typeof count !== "undefined" &&
      typeof countElem !== "undefined" &&
      countElem !== null
    ) {
      countElem.innerHTML = "Count: " + count;
    }
  }
}
