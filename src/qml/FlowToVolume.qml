import QtQuick
// import TableModel
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

TableView {
    anchors.fill: parent
    anchors.topMargin: 42
    anchors.leftMargin: 5
    anchors.rightMargin: 5
    columnSpacing: 1
    rowSpacing: 1
    boundsBehavior: Flickable.StopAtBounds
    model: TableModel {
        TableModelColumn { display: "runCnt" }
        TableModelColumn { display: "name" }
        TableModelColumn { display: "passed" }
        TableModelColumn { display: "from" }
        TableModelColumn { display: "chargeFrom" }
        TableModelColumn { display: "to" }
        TableModelColumn { display: "chargeTo" }
        TableModelColumn { display: "time" }

        // Each row is one type of fruit that can be ordered
        rows: [
        ]
    }
    HorizontalHeaderView {
        id: horizontalHeader
        syncView: expTable
        anchors.left: parent.left
        anchors.right: parent.right
        y: -38
        height:36
        model: ["№", "Имя", "Прошло, л", "Из", "Заряд, л", "В", "Заряд, л", "За время"]
        clip: true
        // movableColumns: false
        Component.onCompleted: test()
    }
    function appendByColumns(columns){
        model.appendRow({
            runCnt: columns[0],
            name: columns[1],
            passed: columns[2],
            from: columns[3],
            chargeFrom: columns[4],
            to: columns[5],
            chargeTo: columns[6],
            time: columns[7]
        })
    }
    function test(){
        model.appendRow({
            runCnt: -1,
            name: "Последний",
            passed: "0",
            from: "LaNi5",
            chargeFrom: "0",
            to: "TiFe",
            chargeTo: "0",
            time: "00:00:00"
        })
    }
    delegate: DelegateChooser {
        DelegateChoice {
            column: 0
            delegate: TextField {
                text: model.display
                readOnly: true
                font.pointSize: 8
                implicitWidth: 42
            }
        }
        DelegateChoice {
            column: 1
            delegate: TextField {
                text: model.display
                readOnly: true
                selectByMouse: true
                font.pointSize: 10
                implicitWidth: 94
                horizontalAlignment: TextInput.AlignHCenter
            }
        }
        DelegateChoice {
            column: 7
            delegate: TextField {
                text: model.display
                readOnly: true
                implicitWidth: 90
                font.pointSize: 10
                inputMask: "99:99:99"
                inputMethodHints: Qt.ImhTime
                horizontalAlignment: TextInput.AlignHCenter
            }
        }
        DelegateChoice {
            delegate: TextField {
                text: model.display
                readOnly: true
                selectByMouse: true
                font.pointSize: 10
                implicitWidth: 76
                horizontalAlignment: TextInput.AlignHCenter
            }
        }
        // DelegateChoice {
        //     column: 0
        //     delegate: CheckBox {
        //         checked: model.display
        //         onToggled: model.display = checked
        //     }
        // }
        // DelegateChoice {
        //     column: 1
        //     delegate: SpinBox {
        //         value: model.display
        //         onValueModified: model.display = value
        //     }
        // }
        // DelegateChoice {
        //     delegate: TextField {
        //         text: model.display
        //         readOnly: true
        //         selectByMouse: true
        //         implicitWidth: 140
        //         onAccepted: model.display = text
        //     }
        // }
    }
}
