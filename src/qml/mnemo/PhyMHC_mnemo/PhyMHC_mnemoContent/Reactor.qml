import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 270
    height: 80
    color: "transparent"
    // radius: 30
    Rectangle{
        z: 0
        y: 5
        // x: 0.1*parent.width/2
        width: parent.width
        height: parent.height - 10
        radius: 0.1*parent.width/2
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "yellow" }
            GradientStop { position: 0.15; color: "#d83632" }
            GradientStop { position: 0.85; color: "#d83632" }
            GradientStop { position: 1.0; color: "yellow" }
        }
        border.color: "#2B2B2B"
        border.width: 4
    }

}
