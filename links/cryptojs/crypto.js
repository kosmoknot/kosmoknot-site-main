function AESencode() {
    let output = document.getElementById("aes-output");
    let input = document.getElementById("aes-input");
    let passcode = document.getElementById("aes-passcode")
    let encrypted = CryptoJS.AES.encrypt(input.value, passcode.value).toString();
    output.innerHTML = encrypted;
}
function AESdecode(){
    let output = document.getElementById("aes-output");
    let input = document.getElementById("aes-input");
    let passcode = document.getElementById("aes-passcode");
    let decrypted = CryptoJS.AES.decrypt(input.value, passcode.value);
    if(decrypted.toString(CryptoJS.enc.Utf8)==""){
        output.innerHTML="unauthorised access denied!"
    }else{
        output.innerHTML=decrypted.toString(CryptoJS.enc.Utf8);
    }
}

function hash(){
    let output = document.getElementById("hash");
    let input = document.getElementById("sha-input");
    let hash = CryptoJS.SHA256(input.value);
    output.innerHTML=hash;
}
