import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
Rectangle {
    id: sensor
    width: 220
    height: 60
    radius: 10
    color: "#c7512e"
    property double value: 0.0012
    property bool showChart: chartShow.checked
    Rectangle {
        id: display
        width: 145
        height: 45
        radius: 10
        color: "#4d9e8a"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 15

        Label {
            id: label
            text: Number(sensor.value.toPrecision(3)).toLocaleString('g') // idk
            font.pixelSize: 17
            color: "white"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 25
        }
        Label {
            id: unitsBar
            text: "л"
            font.pixelSize: 16
            color: "white"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.rightMargin: 22
        }
        Label {
            id: unitsDash
            text: "_____"
            font.pixelSize: 17
            color: "white"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.rightMargin: 9
        }
        Label {
            id: unitsMin
            text: "мин"
            font.pixelSize: 16
            color: "white"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.rightMargin: 13
        }
    }
    Button{
        id: chartShow
        width: 45
        checkable: true
        checked: true
        // highlighted: true
        // Material.theme: Material.Dark
        Material.background: checked ? Material.Orange : Material.Grey
        // Material.elevation: checked ? 0 : 6
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 5
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
    }
}
