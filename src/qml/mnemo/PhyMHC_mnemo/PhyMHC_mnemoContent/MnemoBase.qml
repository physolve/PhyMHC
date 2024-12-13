import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: hMCmnemo.width
    height: hMCmnemo.height
    Image {
        z: 0
        id: hMCmnemo
        source: "background/mnemoscheme.png"
        // fillMode: Image.PreserveAspectFit
        width: 1070
        height: 900
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }

    ValveButton {
        z: 1
        id: valveUps
        x: 823
        y: 315
        checked: scriptDefault.mnemo.valveUpstream
    }
    ValveButton {
        z: 1
        id: valveDowns
        x: 206
        y: 507
        checked: scriptDefault.mnemo.valveDownstream
    }
    Reactor{
        z: 1
        x: 206
        y: 144
    }
    Reactor {
        z: 1
        x: 582
        y: 667
    }
    SensorWidget {
        z: 1
        id: pressureUps
        x: 716
        y: 144
        value: scriptDefault.mnemo.pressureUpstream
    }
    SensorWidget {
        z: 1
        id: pressureDowns
        x: 277
        y: 667
        value: scriptDefault.mnemo.pressureDownstream
    }
    TempWidget {
        id: temperatureUps
        x: 530
        y: 162
        value: scriptDefault.mnemo.temperatureUpstream
    }
    TempWidget {
        id: temperatureDowns
        x: 395
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
}

/*##^##
Designer {
    D{i:0}D{i:1;locked:true}D{i:9}D{i:11}
}
##^##*/
