var answers = {
  "21p1": "2689c3565458bf11077f0a27089791f01f435e28b28da9e844632d034778a2a6",
  "21p2": "de2e69bcace528b5da282acc9f99cfe2794d7d242ce67b64b457baf87214c336",
  "21p3": "545261126165f63e9e6fc3708a12b5bf1db0948e411654c88c6a96583a589353",
  "21p4": "efdd505a4889a9374c310652782bc93e21245003b27f4c9944add33e76305ed0",
  "21p5": "687762cc9c5971490fa34234523b2ac70245ecad7a0cd4ac335fc5b1315b6602",
  "21p6": "8535e86c8118bbbb0a18ac72d15d3a2b37b18d1bce1611fc60165f322cf57386",
  "21p7": "355a61ea1af2c7c19ff24a11722777d74122ac0fafa27d8a954b209be00f55cd",
};

const colCorrect = "#baffc9";
const colIncorrect = "#ffb3ba";

function CheckEnigmaAnswer() {
  var button = event.target;
  var id = button.parentElement.id;
  var input = button.parentElement.getElementsByClassName("EnigmaAnswer")[0];

  if (CryptoJS.SHA256(input.value) == answers[id]) {
    input.style.backgroundColor = colCorrect;
  } else {
    input.style.backgroundColor = colIncorrect;
  }
}
