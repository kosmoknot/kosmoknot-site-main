var cur = -1;
let qBank = [
  {
    qst: "Panipuri panipuri! Name the place!",
    ans: "gypsycorner",
    img: "5.JPG",
  },
  {
    qst: "What did we try together for the first time here?",
    ans: "ganja",
    img: "10.JPG",
  },

  {
    qst: "Name this exquisite desert we had here",
    ans: "tresleches",
    img: "3.JPG",
  },
  {
    qst: "What is missing in this picture?",
    ans: "panties",
    img: "4.JPG",
  },
  {
    qst: "The company that allowed me to work in your company",
    ans: "ansys",
    img: "6.jpg",
  },
  {
    qst: "What is inside the scam can?",
    ans: "fleabagtshirt",
    img: "2.JPG",
  },
  {
    qst: "Traveling in lift means we ____ !!",
    ans: "kiss",
    img: "12.JPG",
  },
  {
    qst: "What do I love stuffing in your mouth?",
    ans: "food",
    img: "8.gif",
  },
  {
    qst: "Who is faster at maths?",
    ans: "aarohi",
    img: "7.jpg",
  },
  {
    qst: "Who loves you from bottom of his heart and will never stop loving you?",
    ans: "anup",
    img: "11.jpg",
  },
  {
    qst: "Happy Birthday! My anti-nihilism!",
    ans: "",
    img: "1.jpg",
  },
];

const checkAnswer = async () => {
  if (cur == -1) {
    cur++;
    setQuestion(cur);
    setStatus(0, 0);
  } else {
    const curAns = document.getElementById("ans").value;
    if (curAns == qBank[cur].ans) {
      cur++;
      if (cur == qBank.length - 1) {
        console.log("The End");
        document.getElementById("answerDiv").style.display = "none";
        document.getElementById("gift").style.display = "block";
      }
      setStatus(1, 1);
      await wait(500);
      setQuestion(cur);
      setStatus(0, 0);
    } else setStatus(0, 1);
  }
};

function wait(time) {
  return new Promise((resolve) => {
    setTimeout(resolve, time);
  });
}

const yourFunction = async () => {
  await wait(5000);
  console.log("Waited 5s");

  await wait(5000);
  console.log("Waited an additional 5s");
};

function setStatus(state, visibility) {
  if (visibility == 1) {
    document.getElementById("statusImg").style.visibility = "visible";
    if (state == 1)
      document.getElementById("statusImg").src =
        "/links/images/bday/correct.png";
    else
      document.getElementById("statusImg").src = "/links/images/bday/wrong.png";
  } else document.getElementById("statusImg").style.visibility = "hidden";
}

function setQuestion(index) {
  document.getElementById("qst").innerText = qBank[index].qst;
  document.getElementById("img").src = "/links/images/bday/" + qBank[index].img;
}
