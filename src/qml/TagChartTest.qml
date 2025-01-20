import QtQuick
import CustomPlot

Item {
    // implicitWidth: 450
    // implicitHeight: 350
    anchors.fill: parent
    CustomPlotItem {
        id: customPlotPressure
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
        width: parent.width;  height: 300
        Component.onCompleted: {
            backend.getCustomPlotPtr(getCustomPlot())
        }
    }
}