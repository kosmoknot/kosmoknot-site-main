import * as THREE from "./three.module.js";
import { DDSLoader } from "./DDSLoader.js";
import { MTLLoader } from "./MTLLoader.js";
import { OBJLoader } from "./OBJLoader.js";
import { OrbitControls } from "./OrbitControls.js";
let camera1, scene1, renderer1, controls1;
let camera2, scene2, renderer2, controls2;
let canvas;
let mirror_assembly = false;
let inter_iit = false;

function onWindowResize() {
  camera1.aspect = window.innerWidth / window.innerHeight;
  camera1.updateProjectionMatrix();

  camera2.aspect = window.innerWidth / window.innerHeight;
  camera2.updateProjectionMatrix();
}

function init1() {
  canvas = document.querySelector("#mirror_assembly");
  if (canvas != null) {
    mirror_assembly = true;
    renderer1 = new THREE.WebGLRenderer({ canvas });
    renderer1.setPixelRatio(window.devicePixelRatio * 2);

    camera1 = new THREE.PerspectiveCamera(
      45,
      window.innerWidth / window.innerHeight,
      1,
      2000
    );
    camera1.position.set(-0.8, -0.8, -0.8);

    scene1 = new THREE.Scene();

    const ambientLight = new THREE.AmbientLight(0xcccccc, 0.4);
    scene1.add(ambientLight);

    const pointLight = new THREE.PointLight(0xffffff, 0.8);
    camera1.add(pointLight);
    scene1.add(camera1);

    controls1 = new OrbitControls(camera1, renderer1.domElement);
    controls1.listenToKeyEvents(window);
    controls1.enableDamping = true;
    controls1.dampingFactor = 0.05;

    controls1.enableZoom = false;

    const manager = new THREE.LoadingManager();
    manager.addHandler(/\.dds$/i, new DDSLoader());

    new MTLLoader(manager)
      .setPath("/links/images/projects/")
      .load("mirror_assembly.mtl", function (materials) {
        materials.preload();

        new OBJLoader(manager)
          .setMaterials(materials)
          .setPath("/links/images/projects/")
          .load("mirror_assembly.obj", function (object) {
            object.position.set(0, 0, 0);
            scene1.add(object);
          });
      });

    window.addEventListener("resize", onWindowResize);
  }
}

function animate1() {
  controls1.update();
  requestAnimationFrame(animate1);
  renderer1.render(scene1, camera1);
}

function init2() {
  canvas = document.querySelector("#inter_iit");
  if (canvas != null) {
    inter_iit = true;
    renderer2 = new THREE.WebGLRenderer({ canvas });
    renderer2.setPixelRatio(window.devicePixelRatio * 2);

    camera2 = new THREE.PerspectiveCamera(
      45,
      window.innerWidth / window.innerHeight,
      1,
      2000
    );
    camera2.position.set(-800, -800, -800);

    scene2 = new THREE.Scene();

    const ambientLight = new THREE.AmbientLight(0xcccccc, 0.4);
    scene2.add(ambientLight);

    const pointLight = new THREE.PointLight(0xffffff, 0.8);
    camera2.add(pointLight);
    scene2.add(camera2);

    controls2 = new OrbitControls(camera2, renderer2.domElement);
    controls2.listenToKeyEvents(window);
    controls2.enableDamping = true;
    controls2.dampingFactor = 0.05;

    controls2.enableZoom = false;

    const manager = new THREE.LoadingManager();
    manager.addHandler(/\.dds$/i, new DDSLoader());

    new MTLLoader(manager)
      .setPath("/links/images/projects/")
      .load("inter_iit.mtl", function (materials) {
        materials.preload();

        new OBJLoader(manager)
          .setMaterials(materials)
          .setPath("/links/images/projects/")
          .load("inter_iit.obj", function (object) {
            object.position.set(0, 0, 0);
            scene2.add(object);
          });
      });

    window.addEventListener("resize", onWindowResize);
  }
}

function animate2() {
  controls2.update();
  requestAnimationFrame(animate2);
  renderer2.render(scene2, camera2);
}

init1();
init2();

if (mirror_assembly == true) animate1();
if (inter_iit == true) animate2();
