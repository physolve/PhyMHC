import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
Item {
    anchors.fill: parent
    anchors.topMargin: 10
    anchors.leftMargin: 5
    anchors.rightMargin: 5
    anchors.bottomMargin: 5
    ScrollView {
        id: view
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 600
        // approach as listview later
        TextArea {
            text: scriptDefault.infoString
            font.family: "Helvetica"
            font.pointSize: 13
            font.bold: true
        }
    }
    Column{
        anchors.top: view.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        spacing: 10
        Button{
            width: 160
            height: 50
            text: "1. test"
            anchors.horizontalCenter: parent.horizontalCenter
            Material.roundedScale: Material.MediumScale
            onClicked: scriptDefault.firstTask()
        }
        Button{
            width: 160
            height: 50
            text: "2. values to STP"
            anchors.horizontalCenter: parent.horizontalCenter
            Material.roundedScale: Material.MediumScale
            onClicked: scriptDefault.secondTask()
        }
        Button{
            width: 160
            height: 50
            text: "3. Temperature transition"
            anchors.horizontalCenter: parent.horizontalCenter
            Material.roundedScale: Material.MediumScale
            onClicked: scriptDefault.thirdTask()
        }

    }

}
