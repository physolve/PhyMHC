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
        anchors.fill: parent

        // approach as listview later
        
        TextArea {
            text: scriptDefault.infoString
            font.family: "Helvetica"
            font.pointSize: 13
            font.bold: true
        }
    }

}
