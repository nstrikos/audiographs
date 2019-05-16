function setBorderColor() {
    if (isActive)
        return "red"
    else
        return "gray"
}

function focusChanged() {
    if (activeFocus) {
        isActive = true
        //androidClient.speak(buttonText.text)
        //androidClient.vibrate("500")
        texttospeech.speak(buttonText.text)
    }
    else {
        isActive = false
    }
}
