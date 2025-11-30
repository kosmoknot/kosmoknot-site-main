const canvas = document.getElementById("fireworksCanvas");
const ctx = canvas.getContext("2d");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const particles = [];

function random(min, max) {
  return Math.random() * (max - min) + min;
}

function Particle(x, y, color) {
  this.x = x;
  this.y = y;
  this.color = color;
  this.radius = random(2, 4);
  this.speedX = random(-2, 2);
  this.speedY = random(-2, 2);
  this.alpha = 1;

  this.draw = function () {
    ctx.globalAlpha = this.alpha;
    ctx.beginPath();
    ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
    ctx.fillStyle = this.color;
    ctx.fill();
    ctx.closePath();
  };

  this.update = function () {
    this.x += this.speedX;
    this.y += this.speedY;
    this.alpha -= 0.01;
  };
}

function createFirework(x, y) {
  const colors = ["#ff004f", "#ffdd00", "#00ff59", "#00c7ff", "#ad00ff"];
  for (let i = 0; i < 100; i++) {
    const color = colors[Math.floor(Math.random() * colors.length)];
    particles.push(new Particle(x, y, color));
  }
}

function animate() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  particles.forEach((particle, index) => {
    particle.draw();
    particle.update();

    if (particle.alpha <= 0) {
      particles.splice(index, 1);
    }
  });

  requestAnimationFrame(animate);
}

document.addEventListener("click", (e) => {
  createFirework(e.clientX, e.clientY);
});

animate();
