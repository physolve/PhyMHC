import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Item{
    anchors.fill: parent
    property date currentDate: new Date()
    function updateFilePath(){
        let newName = ""
        newName = currentDate.toLocaleString(Qt.locale(),"yyyy-MM-dd")
        if(fromChoose.currentIndex != -1)
            newName+="_"+fromChoose.currentText
        else newName+= "_Из"
        if(toChoose.currentIndex != -1)
            newName+="_"+toChoose.currentText
        else newName+= "_В"
        let dayRuns = runConfig.totalRuns
        if(dayRuns > 0)
            newName+= "_"+dayRuns
        fileName.text = newName
    }

    function startRun(){
        let m_parameters = []
        if(!passRunConfig(m_parameters)){
            console.log("Wrong parameters (1)")
            startScalarCalc.checked = false
            return
        }
        if(!backend.passRunParametersGui(m_parameters)){
            startScalarCalc.checked = false
            return
        }
        backend.runFromGui()
    }

    function stopRun(){
        // savings clearing
        backend.stopFromGui()
    }

    function passRunConfig(parameters){
        if(runName.text) parameters.push(runName.text) // runName 0
        else parameters.push("Empty")
        
        if(fromChoose.currentIndex == -1){
            return false
        }
        parameters.push(fromChoose.currentText) // releaseFrom 1
        
        if(initialFrom.text) parameters.push(initialFrom.text) // initialLitresFrom 2
        else parameters.push(0)
        
        if(toChoose.currentIndex == -1){
            return false
        }
        parameters.push(toChoose.currentText) // loadTo 3
        
        if(initialTo.text) parameters.push(initialTo.text) // initialLitresTo 4
        else parameters.push(0)
        // upstreamToDownstream 5
        // downstreamToUpstream 6
        // upstreamToAir 7
        // downstreamToAir 8
        if(fromChoose.currentText == "LaNi5"&&toChoose.currentText == "TiFe"){
            parameters.push(true)
            parameters.push(false)
            parameters.push(false)
            parameters.push(false)
        }
        else if(fromChoose.currentText == "TiFe"&&toChoose.currentText == "LaNi5"){
            parameters.push(false)
            parameters.push(true)
            parameters.push(false)
            parameters.push(false)
        }
        else if(fromChoose.currentText == "LaNi5"&&toChoose.currentText == "воздух"){
            parameters.push(false)
            parameters.push(false)
            parameters.push(true)
            parameters.push(false)
        }
        else if(fromChoose.currentText == "TiFe"&&toChoose.currentText == "воздух"){
            parameters.push(false)
            parameters.push(false)
            parameters.push(false)
            parameters.push(true)
        }
        else{
            console.log("Wrong parameters")
            // show error message
            return false
        }

        if(logComment.text) parameters.push(logComment.text) // logHeaderComment 9
        else parameters.push("No comments")

        return true
    }
    Label {
        id: logTextDisplay
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
        color: "black"
        text: "Промежуточная информация" //backend.logText
        font.pointSize: 14
        padding: 5
        background: Rectangle{
                radius: 20
                height: 50
                color: Material.color(Material.DeepOrange,Material.Shade100)
            }
    }
    RowLayout{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        // anchors.horizontalCenter: parent.horizontalCenter
        // width: 500
        anchors.leftMargin: 20
        anchors.rightMargin: 40
        anchors.topMargin: 110
        spacing: 10
        Layout.alignment: Qt.AlignHCenter
        TextField{
            id: runName
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.3
            // property int curRunCnt:  flowToVolume ? flowToVolume.runCnt : 0
            // text: "Запуск #" + curRunCnt
            font.pointSize: 12
            placeholderText: "Имя запуска"
            horizontalAlignment: TextInput.AlignHCenter
        }
        ComboBox {
            id: fromChoose
            Layout.fillHeight: true
            currentIndex: -1
            model: ["LaNi5", "TiFe"]
            displayText: "Из " + currentText
            onActivated: {
                updateFilePath()
            }
        }
        ComboBox {
            id: toChoose
            Layout.fillHeight: true
            currentIndex: -1
            model: ["LaNi5", "TiFe", "воздух"]
            displayText: "В " + currentText
            onActivated: {
                updateFilePath()
            }
        }
        TextField{
            id: fileName
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.3
            // property int curRunCnt:  flowToVolume ? flowToVolume.runCnt : 0
            // text: "Запуск #" + curRunCnt
            font.pointSize: 10
            placeholderText: "Имя файла"
            horizontalAlignment: TextInput.AlignHCenter
            Component.onCompleted: updateFilePath()
            // {
            //     text = currentDate.toLocaleString(Qt.locale(),"yyyy-MM-dd")+"_Из_В";
            // }
        }
    }
    RowLayout{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 210
        anchors.rightMargin: 205
        anchors.topMargin: 160
        // anchors.horizontalCenter: parent.horizontalCenter
        TextField{
            id: initialFrom
            Layout.fillHeight: true
            font.pointSize: 12
            // text: "0"
            validator: DoubleValidator {bottom: 0; top: 1000; decimals: 2}
            placeholderText: "Заряд л. "
            horizontalAlignment: TextInput.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }
        TextField{
            id: initialTo
            Layout.fillHeight: true
            font.pointSize: 12
            // text: "0"
            validator: DoubleValidator {bottom: 0; top: 1000; decimals: 2}
            placeholderText: "Заряд л."
            horizontalAlignment: TextInput.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }
    }
    TextField{
        id: logComment
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 215
        height: 80
        // text : flowToVolume ? flowToVolume.scalarStr : ""
        font.pointSize: 12
        placeholderText: "Комментарий в шапку лога"
        horizontalAlignment: TextInput.AlignHCenter
    }

    RowLayout{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        // anchors.horizontalCenter: parent.horizontalCenter
        // width: 500
        anchors.leftMargin: 20
        anchors.rightMargin: 40
        anchors.topMargin: 310
        spacing: 5
        Layout.alignment: Qt.AlignHCenter
        TextField{
            id: scalar
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.3
            text : runConfig.totalLitres
            readOnly: true
            font.pointSize: 12
            placeholderText: "Итого литров"
            horizontalAlignment: TextInput.AlignHCenter
        }
        TextField{
            id: duration
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.3
            text: runConfig.duration
            font.pointSize: 12
            readOnly: true
            inputMask: "99:99:99"
            inputMethodHints: Qt.ImhTime
            placeholderText: "За время"
            horizontalAlignment: TextInput.AlignHCenter
        }
        Button{
            id: startScalarCalc
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.2
            checkable: true
            checked: backend.actualRun
            text: checked ? "Стоп" : "Начать"
            font.pixelSize: 13
            // onClicked: flowToVolume ? flowToVolume.onFlowToScalarClicked(runName.text, checked) : doNothing()
            onClicked: checked ? startRun() : stopRun()
        }
        Switch{
            display: AbstractButton.TextUnderIcon
            text: checked ? "Считаю" : "Не считаю"
            checked: backend.actualReading
            // pause click
        }
    }
    ScrollView {
        id: tableScrollExp
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 380
        height: 350
        background: Rectangle {
            anchors.fill: parent
            opacity: 0.3
            color: "#a5a4a4"
        }
        FlowToVolume{
            id: expTable
            
            // onClicked: function(row, rowData) { print('onClicked', row, JSON.stringify(rowData)); }
        }
        contentWidth: children.implicitWidth
        contentHeight: children.implicitHeight
        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        function scrollToBottom(){
            ScrollBar.vertical.position = 1.0 - ScrollBar.vertical.size
        }
        clip: true
    }
    Button{
        id: testTableChange
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.topMargin: 760
        text: "Проверка добавления строки"
        font.pixelSize: 13
        onClicked: {
            expTable.test()
            tableScrollExp.scrollToBottom()
        }
    }
    Button{
        id: saveResult
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 760
        text: "Сохранить"
        font.pixelSize: 13
        // onClicked: fileDialog.open()
    }
    FileDialog {
        id: fileDialog
        title: "Save Dialog"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Text files (*.txt)"]
        // onAccepted: flowToVolume ? flowToVolume.saveResults(selectedFile) : doNothing()
    }

}