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
        id: valveUps
        x: 719
        y: 315
        checked: backend.vUpState // scriptDefault.mnemo.valveUpstream
        // onClicked: scriptDefault.valveUpstreamChanged(checked)
        onClicked: backend.vUpState = checked
    }
    ValveButton {
        z: 1
        id: valveDowns
        x: 325
        y: 507
        checked: backend.vDwState // scriptDefault.mnemo.valveDownstream
        onClicked: backend.vDwState = checked
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
        x: 203
        y: 120
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
        x: 470
        y: 210
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

    SensorWidget {
        z: 1
        id: pressureUps
        x: 658
        y: 144
        value: scriptDefault.mnemo.pressureUpstream
    }
    SensorWidget {
        z: 1
        id: pressureDowns
        x: 325
        y: 667
        value: scriptDefault.mnemo.pressureDownstream
    }
    TempWidget {
        id: temperatureUps
        x: 514
        y: 160
        value: scriptDefault.mnemo.temperatureUpstream
    }
    TempWidget {
        id: temperatureDowns
        x: 414
        y: 683
        value: scriptDefault.mnemo.temperatureDownstream
    }

    FlowMeterWidget {
        id: flowMeterUps
        x: 332
        y: 302
        value: scriptDefault.mnemo.flowUpstream
    }

    FlowMeterWidget {
        id: flowMeterDowns
        x: 530
        y: 494
        value: scriptDefault.mnemo.flowDownstream
    }

    ValveButton {
        id: valveVacuum
        x: 908
        y: 484
        z: 1
        checked: scriptDefault.mnemo.valveVacuum
    }

}

/*##^##
Designer {
    D{i:0}D{i:1;locked:true}
}
##^##*/
