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
        source: "background/mnemoscheme_beta.png"
        // fillMode: Image.PreserveAspectFit
        width: 1070
        height: 900
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }
    GasTank {
        z:1
        id: gasTank
        x: 36
        y: 275
    }
    ValveButton {
        z: 1
        id: valveDowns
        x: 719
        y: 315
        checked: backend.vDwState
        onClicked: backend.vDwState = checked
    }
    ValveButton {
        z: 1
        id: valveUps
        x: 325
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
        x: 203
        y: 144
    }
    Switch{
        id: heaterSwitchUp
        x: 210
        y: 109
        height: 35
        z: 0
        text: qsTr("Heater")
        checked: backend.hUpState
        onClicked: backend.hUpState = checked
    }

    Cooler{
        z: 0
        x: 218
        y: 199
        cooling: backend.coolUpState
    }
    Cooler {
        x: 303
        y: 199
        z: 0
        cooling: backend.coolUpState
    }
    Cooler {
        x: 388
        y: 199
        z: 0
        cooling: backend.coolUpState
    }
    Switch{
        id: fanSwitchUp
        x: 360
        y: 109
        z: 0
        text: qsTr("Fans")
        checked: backend.coolUpState
        onClicked: backend.coolUpState = checked
    }

    Reactor {
        z: 1
        x: 582
        y: 667
    }
    Switch {
        id: heaterSwitchDw
        x: 615
        y: 634
        height: 35
        text: qsTr("Heater")
        z: 0
        checked: backend.hDwState
        onClicked: backend.hDwState = checked
    }

    Cooler {
        x: 594
        y: 722
        z: 0
    }

    Cooler {
        x: 679
        y: 722
        z: 0
    }
    Cooler {
        x: 764
        y: 722
        z: 0
    }
    Switch {
        id: fanSwitchDw
        x: 741
        y: 634
        text: qsTr("Fans")
        z: 0
        checked: backend.coolDwState
        onClicked: backend.coolDwState = checked
    }

    SensorWidget {
        z: 1
        id: pressureUps
        x: 658
        y: 144
        value: backend.guiVals.pressureUpstream
    }
    SensorWidget {
        z: 1
        id: pressureDowns
        x: 325
        y: 667
        value: backend.guiVals.pressureDownstream
    }
    TempWidget {
        id: temperatureUps
        x: 514
        y: 160
        value: backend.guiVals.temperatureUpstream
    }
    TempWidget {
        id: temperatureDowns
        x: 414
        y: 683
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
        x: 908
        y: 484
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
