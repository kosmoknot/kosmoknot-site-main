$Header()$
 <style media="screen">
  .enter {
   display: block;
   border: whitesmoke;
   border-style: solid;
   border-width: thick;
   width: 100%;
   text-align: center;
   font-size: 50px;
   color: #c9cacc;
  }

  .enter a:hover {
   color: #2bbc8a;
  }

  .enter a {
   color: #c9cacc;
   text-decoration: none;
  }
 </style>
  <script type="module">
  import * as THREE from '/links/three/three.module.js';
  import { OrbitControls } from '/links/three/OrbitControls.js';
  const scene = new THREE.Scene();
  const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

  const renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setSize(window.innerWidth, window.innerHeight);
  document.body.appendChild(renderer.domElement);
  window.addEventListener('resize', () => {
   renderer.setSize(window.innerWidth, window.innerHeight);
   camera.aspect = window.innerWidth / window.innerHeight;
   camera.updateProjectionMatrix();
  })
  const loader = new THREE.TextureLoader();
  const geometry = new THREE.PlaneGeometry(5.52, 6.97, 5);
  const material = new THREE.MeshBasicMaterial({ map: loader.load('/links/images/articles/home.jpg'), side: THREE.DoubleSide });
  const plane = new THREE.Mesh(geometry, material);
  scene.add(plane);

  camera.position.z = 5;

  let controls = new OrbitControls(camera, renderer.domElement);
  controls.listenToKeyEvents(window);
  controls.enableDamping = true;
  controls.dampingFactor = 0.05;

  controls.screenSpacePanning = false;

  controls.minDistance = 5;
  controls.maxDistance = 10;

  const animate = function () {
   requestAnimationFrame(animate);
   renderer.render(scene, camera);
  };
  animate();
 </script>
