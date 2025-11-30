import * as THREE from "./three.module.js";
import { DDSLoader } from "./DDSLoader.js";
import { MTLLoader } from "./MTLLoader.js";
import { OBJLoader } from "./OBJLoader.js";
import { OrbitControls } from "./OrbitControls.js";
let camera, scene, renderer, controls;

function load(id, path, name, cx, cy, cz, ox, oy, oz) {
  var name_obj = name + ".obj";
  var name_mtl = name + ".mtl";
  init(id, path, name_obj, name_mtl, cx, cy, cz, ox, oy, oz);
  animate();
}

function init(id, path, name_obj, name_mtl, cx, cy, cz, ox, oy, oz) {
  const canvas = document.getElementById(id);
  renderer = new THREE.WebGLRenderer({ canvas });
  renderer.setPixelRatio(window.devicePixelRatio * 2);

  camera = new THREE.PerspectiveCamera(
    45,
    window.innerWidth / window.innerHeight,
    1,
    2000
  );
  camera.position.set(cx, cy, cz);

  scene = new THREE.Scene();

  const ambientLight = new THREE.AmbientLight(0xcccccc, 0.4);
  scene.add(ambientLight);

  const pointLight = new THREE.PointLight(0xffffff, 0.8);
  camera.add(pointLight);
  scene.add(camera);

  controls = new OrbitControls(camera, renderer.domElement);
  controls.listenToKeyEvents(window);
  controls.enableDamping = true;
  controls.dampingFactor = 0.05;

  controls.enableZoom = false;

  const manager = new THREE.LoadingManager();
  manager.addHandler(/\.dds$/i, new DDSLoader());

  new MTLLoader(manager).setPath(path).load(name_mtl, function (materials) {
    materials.preload();

    new OBJLoader(manager)
      .setMaterials(materials)
      .setPath("/links/images/projects/")
      .load(name_obj, function (object) {
        object.position.set(ox, oy, oz);
        scene.add(object);
      });
  });

  window.addEventListener("resize", onWindowResize);
}

function onWindowResize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
}

function animate() {
  requestAnimationFrame(animate);
  renderer.render(scene, camera);
}

export { load };
