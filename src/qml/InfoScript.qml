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
        Row{
            spacing: 10
            Button{
                width: 200
                height: 50
                text: "1. test"
                //anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.firstTask()
            }
            Button{
                width: 200
                height: 50
                text: "2. values to STP"
                //anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.secondTask()
            }
        }
        Row{
            spacing: 10
            Connections{
                target: scriptDefault
                function onThirdTaskDone(){
                    thirdTaskButton.checked = false
                }
            }
            Button{
                id: thirdTaskButton
                width: 200
                height: 50
                checkable: true
                text: "3. Temperature transition"
                //anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.thirdTask()
            }
            Connections{
                target: scriptDefault
                function onFourthTaskDone(){
                    fourthTaskButton.checked = false
                }
            }
            Button{
                id: fourthTaskButton
                width: 200
                height: 50
                checkable: true
                text: "4. Flow transition"
                //anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.fourthTask()
            }
        }
        Row{
            spacing: 10
            Button{
                id: fifthTaskButton
                width: 200
                height: 50
                checkable: true
                text: "5. Flow to Reactor pressure"
                // anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.fifthTask(checked)
            }
            Button{
                id: manualPrepare
                width: 200
                height: 50
                text: "6. Gas supply and valves"
                // anchors.horizontalCenter: parent.horizontalCenter
                Material.roundedScale: Material.MediumScale
                onClicked: scriptDefault.manualPrepare()
            }
        }
        Button{
            id: manualTestController
            width: 200
            height: 50
            // checkable: true
            text: "7. Manual start of test controller"
            // anchors.horizontalCenter: parent.horizontalCenter
            Material.roundedScale: Material.MediumScale
            onClicked: backend.manualTestControllerStart()
        }
    }

}
