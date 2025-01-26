import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12
import QtCharts
import "mnemo/PhyMHC_mnemo/PhyMHC_mnemoContent"
ApplicationWindow {
    id: main
    width: 1660
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
            // ValuesAxis {
            //     id: lineOneAxisX
            //     max: 100
            //     visible: true
            //     gridVisible: true
            //     labelsVisible: false
            // }
            // ValueAxis {
            //     id: lineOneAxisY
                
            //     visible: true
            //     // min: -0.5
            //     max: 1e-7
            //     labelFormat: "%g"
            //     tickCount: 3
            //     labelsFont.pointSize: 9
            //     labelsFont.bold: false
            //}


            // ChartView {
            //     x: 330
            //     y: 360
            //     height: 100
            //     width: 230
            //     antialiasing: true
            //     visible: parent.flowUpstreamShowChart
            //     margins.left: 0
            //     margins.right: 0
            //     margins.top: 0
            //     margins.bottom: 0

            //     legend.visible: false
            //     backgroundRoundness: 5
            //     theme: ChartView.ChartThemeBlueCerulean
            //     LineSeries {
            //         id: lineOne
            //         name: "flow [slpm]"
            //         color: "white"
            //         width: 1
            //         axisX: lineOneAxisX
            //         axisY: lineOneAxisY
            //         // axisYRight: splineChartAxisY
            //         Connections{
            //             target: scriptDefault
            //             function onMnemoChanged(){
            //                 lineOne.append(lineOne.count, scriptDefault.mnemo.flowUpstream);
            //                 lineOneAxisX.max = lineOneAxisX.max < lineOne.count ? lineOne.count + 100 : lineOneAxisX.max
            //                 lineOneAxisX.min = lineOne.count > 100 ? lineOne.count - 100 : lineOneAxisX.min
            //                 lineOneAxisY.max = lineOneAxisY.max < scriptDefault.mnemo.flowUpstream ? scriptDefault.mnemo.flowUpstream : lineOneAxisY.max
            //             } 
            //         }
            //     }
            // }

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
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    TagChartTest{
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
                            parameters: [ "Valve upstream", "Valve downstream", "Valve supply",
                            "Cooler upstream", "Cooler downstream", "Heater upstream", "Heater downstream", 
                            "skip",
                            "Flow upstream", "Flow downstream"]
                             color: backend.digitalConnected ? "#536872" : "#000000"
                        }
                    }
                }
            } 
        }
    }
}
