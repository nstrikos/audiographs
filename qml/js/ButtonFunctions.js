function setTextColor() {
//    if (isActive) {
//        if (isPressed)
//            return "black"
//        else
//            return "gray"
//    }
//    else {
//        if (isPressed)
//            return "black"
//        else
//            return "gray"
//    }
    return "black"
}

function setBorderColor() {
    if (isActive)
        return "red"
    else
        return "gray"
}

function focusChanged() {

    if (activeFocus) {
        isActive = true
        androidClient.speak(buttonText.text)
    }
    else {
        isActive = false
    }
}

function clear() {
    parametersButton.isPressed = false
    parametersButton.isActive = false
    parametersRect.visible = false

    graphButton.isPressed = false
    graphButton.isActive = false
    graphRect.visible = false

    rect2Button.isPressed = false
    rect2Button.isActive = false
    rect2.visible = false

    tableButton.isPressed = false
    tableButton.isActive = false
    rect3.visible = false
}
