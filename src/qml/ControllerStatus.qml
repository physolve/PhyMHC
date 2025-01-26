import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: customBack
    implicitWidth: 250
    implicitHeight: 400
    color: "transparent"
    border.color : "steelblue" 
    border.width : 8
    required property string name
    required property var parameters
    
    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10
        Label{
            Layout.alignment: Qt.AlignCenter
            font.pointSize: 16
            color: "white"
            text: name
        }    
        Label{
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 13
            color: "white"
            text:  "Channels info" 
        }
        ListView {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: parameters
            spacing: 5
            delegate:  Rectangle {
                color: "#36454f" //Material.BlueGrey
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5
                height: 25
                Row{
                    spacing: 10
                    Text { text: `Ch.${index}` ; font.pointSize: 12; color: "white" }
                    Text { text: modelData; font.pointSize: 12; color: "white" } //.parameter
                }
            }
            // focus: true
            interactive: false
        }
    }
}