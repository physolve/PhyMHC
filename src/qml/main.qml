import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
import "mnemo/PhyMHC_mnemo/PhyMHC_mnemoContent"
ApplicationWindow {
    id: main
    width: 1550
    height: 910
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    visible: true
    title: qsTr("PhyMHC")
    // visibility: Window.Maximized
    // Material.theme: Material.Dark
    // Material.accent: Material.Indigo
    // font.capitalization: Font.MixedCase
    SplitView {
        id: grid
        anchors.fill: parent
        MnemoBase{
            id: mnemoBase
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 5
            SplitView.minimumWidth: 1080
        }
        Item{
            // SplitView.minimumWidth: 500
            // SplitView.preferredWidth: 670
            TabBar {
                id: barMain
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                //anchors.right: parent.right
                //height: 100
                Repeater{
                    id: barMainRepeater
                    model: ["Info", "Graph", "Settings"]
                    TabButton{
                        text: modelData
                        width: Math.max(120, barMain.width/3)
                        font.pointSize: 12
                    }
                }
            }
            StackLayout {
                id: layoutMain
                //Layout.fillWidth: true
                //width: 600
                //height: 800
                anchors.top: barMain.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                //width: parent.width
                currentIndex: barMain.currentIndex
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    InfoScript{
                    }
                }   
                Item{
                    //Layout.fillHeight: true
                    Rectangle{
                        id: test2
                        width: 100; height: 100
                    }
                }
                
                Item{
                    //Layout.fillHeight: true
                    Rectangle{
                        id: test3
                        width: 100; height: 100
                    }
                }
            } 
        }
    }
}
