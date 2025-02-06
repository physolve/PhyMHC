import QtQuick
import QtQuick.Controls
Item {
    id: root
    width: hMCmnemo.width
    height: hMCmnemo.height
    property bool flowUpstreamShowChart: flowMeterUps.showChart
    Image {
        z: 0
        id: hMCmnemo
        source: "background/mnemoscheme_gamma.png"
        // fillMode: Image.PreserveAspectFit
        width: 1070
        height: 900
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }
    GasTank {
        z:1
        id: gasTank
        x: 921
        y: 280
    }
    ValveButton {
        z: 1
        id: valveDowns
        x: 621
        y: 315
        checked: backend.vDwState
        onClicked: backend.vDwState = checked
    }
    ValveButton {
        z: 1
        id: valveUps
        x: 424
        y: 507
        checked: backend.vUpState
        onClicked: backend.vUpState = checked
    }
    Connections{
        target: scriptDefault
        function onMnemoChanged(){
            let intence = (scriptDefault.mnemo.temperatureUpstream-scriptDefault.targetvals.tempStartUpstream)/(scriptDefault.targetvals.tempTargetUpstream-scriptDefault.targetvals.tempStartUpstream)
            if (intence > 1) intence = 1
            reactorUpstream.makeBrighter(intence)
        } 
    }
    Reactor{
        id: reactorUpstream
        z: 1
        x: 578
        y: 147
    }
    Switch{
        id: heaterSwitchUp
        x: 585
        y: 112
        height: 35
        z: 0
        text: qsTr("Heater")
        checked: backend.hUpState
        onClicked: backend.hUpState = checked
    }

    Cooler{
        z: 0
        x: 593
        y: 202
        cooling: backend.coolUpState
    }
    Cooler {
        x: 678
        y: 202
        z: 0
        cooling: backend.coolUpState
    }
    Cooler {
        x: 763
        y: 202
        z: 0
        cooling: backend.coolUpState
    }
    Switch{
        id: fanSwitchUp
        x: 735
        y: 112
        z: 0
        text: qsTr("Fans")
        checked: backend.coolUpState
        onClicked: backend.coolUpState = checked
    }

    Reactor {
        z: 1
        x: 221
        y: 635
    }
    Switch {
        id: heaterSwitchDw
        x: 253
        y: 605
        height: 35
        text: qsTr("Heater")
        z: 0
        checked: backend.hDwState
        onClicked: backend.hDwState = checked
    }

    Cooler {
        x: 233
        y: 690
        z: 0
        cooling: backend.coolDwState
    }

    Cooler {
        x: 318
        y: 690
        z: 0
        cooling: backend.coolDwState
    }
    Cooler {
        x: 403
        y: 690
        z: 0
        cooling: backend.coolDwState
    }
    Switch {
        id: fanSwitchDw
        x: 379
        y: 605
        text: qsTr("Fans")
        z: 0
        checked: backend.coolDwState
        onClicked: backend.coolDwState = checked
    }

    SensorWidget {
        z: 1
        id: pressureUps
        x: 253
        y: 144
        value: backend.guiVals.pressureUpstream
    }
    SensorWidget {
        z: 1
        id: pressureDowns
        x: 724
        y: 635
        value: backend.guiVals.pressureDownstream
    }
    TempWidget {
        id: temperatureUps
        x: 407
        y: 160
        value: backend.guiVals.temperatureUpstream
    }
    TempWidget {
        id: temperatureDowns
        x: 521
        y: 651
        value: backend.guiVals.temperatureDownstream
    }

    FlowMeterWidget {
        id: flowMeterUps
        x: 530
        y: 494
        value: backend.guiVals.flowUpstream
    }

    FlowMeterWidget {
        id: flowMeterDowns
        x: 332
        y: 302
        value: backend.guiVals.flowDownstream
    }

    ValveButton {
        id: valveVacuum
        x: 115
        y: 422
        z: 1
        checked: backend.vVaState
        onClicked: backend.vVaState = checked
    }

}

/*##^##
Designer {
    D{i:0}D{i:1;locked:true}
}
##^##*/
