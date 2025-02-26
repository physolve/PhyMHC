import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
// import QtCharts
import "mnemo/PhyMHC_mnemo/PhyMHC_mnemoContent"
ApplicationWindow {
    id: main
    width: 1750
    height: 910
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    visible: true
    title: qsTr("PhyMHC")
    // visibility: Window.Maximized
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
            TabBar {
                id: barMain
                width: parent.width
                anchors.top: parent.top
                anchors.left: parent.left
                Repeater{
                    id: barMainRepeater
                    model: ["Измерение", "График", "Дополнительно", "Настройки"]
                    TabButton{
                        text: modelData
                        width: Math.max(90, barMain.width/4)
                        font.pointSize: 12
                    }
                }
            }
            StackLayout {
                id: layoutMain
                anchors.top: barMain.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                currentIndex: barMain.currentIndex
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    DataWindow{
                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    TagChartTest{
                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    InfoScript{
                    }
                } 
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout{
                        spacing: 10

                        ControllerStatus{
                            name: "USB-2019"
                            parameters: [ "Temperature upstream", "Pressure upstream", "Flow upstream", 
                            "Temperature downstream", "Pressure downstream", "Flow downstream"]
                                // {
                                //     parameter: "temperature upstream"
                                // },
                            //]
                            color: backend.analogConnected ? "#536872" : "#000000"
                            Connections {
                                target: backend // backend?
                                function onAnalogConnectedChanged() { 
                                    parent.setConnected()
                                }
                            }
                        }
                        ControllerStatus{
                            name: "USB-2045"
                            parameters: [ "Valve upstream", "Valve downstream", "Valve vacuum",
                            "Cooler upstream", "Cooler downstream", "Heater upstream", "Heater downstream", 
                            "skip"]
                            color: backend.digitalConnected ? "#536872" : "#000000"
                        }
                    }
                }
            } 
        }
    }
}
