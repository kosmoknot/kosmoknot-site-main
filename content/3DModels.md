$Header()$
<script src="../links/three/load_models.module.js"></script>
<script type="module">
import { load } from "../links/three/load_models.module.js";
window.loadModel = loadModel;

function loadModel() {
    var name = document.getElementById("models");
    if (name.value == 'mirror_assembly') {
        load('models_show', '../links/images/projects/', 'mirror_assembly', -0.8, -0.8, -0.8, 0, 0, 0);
    }
    else {
        load('models_show', '../links/images/projects/', 'inter_iit', -800, -800, -800, 0, 0, 0);
    }
}
</script>

$Title()$
<form>
<label for="models">Choose a model:</label> <br>
<select id="models" name="models">
<option value="mirror_assembly">Mirror assembly</option>
<option value="inter_iit">Ergonomic crutches</option>
</select>
<button type="button" id="sub_button" name="submit" onclick="loadModel();">Load</button>
<p style="font-size:16px;">(Loading might be slow depending on your RAM and netspeed)</p>
</form>
<canvas id="models_show"></canvas>


$Footer()$
