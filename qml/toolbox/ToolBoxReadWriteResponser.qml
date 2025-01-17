import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SAK.Custom
import "../common"

Item {
    id: root

    property SAKResponserTool responserTool: null

    QtObject {
        id: settingKeys
        readonly property string items: groupName + "/responser/items"
    }

    ToolBoxCommonTableView {
        id: tableView
        anchors.fill: parent
        tableMode: responserTool ? responserTool.tableModel : null
        tableHeaders: responserTool ? responserTool.headers : []
        fillWidthColumns: [11, 21]
        showColumns: [0, 1, 2, 11, 21]
        tabelModelTool: root.responserTool
        itemsKey: settingKeys.items
        onInvokeAppend: {
            var parameters = responserTool.itemContext(-1)
            editorPopup.setParameters(parameters)
            editorPopup.index = -1
            editorPopup.open()
        }
        onInvokeEdit: {
            var parameters = responserTool.itemContext(currentRowIndex)
            editorPopup.setParameters(parameters)
            editorPopup.index = currentRowIndex
            editorPopup.open()
        }
        onItemsChanged: updateSettings()
    }

    ToolBoxReadWriteResponserPopup {
        id: editorPopup
        onRejected: close()
        onAccepted: {
            close()
            var parameters = getParameters()
            responserTool.addItem(JSON.stringify(parameters), index)

            updateSettings()
        }

        property int index: -1
    }

//    Component.onCompleted: {
//        var hexString = sakSettings.value(settingKeys.items)
//        var jsonString = sakInterface.hexString2String(hexString);
//        var jsonArray = JSON.parse(jsonString)
//        if (jsonArray) {
//            for (var i = 0; i < jsonArray.length; i++) {
//                var item = jsonArray[i]
//                responserTool.addItem(JSON.stringify(item), -1)
//            }
//        }
//    }

    function updateSettings() {
        sakSettings.edRemove(settingKeys.group, settingKeys.array)
        var items = responserTool.itemsContext()
        if (items.length) {
            var itemStringList = []
            for (var i = 0; i < items.length; i++) {
                var item = items[i]
                var itemString = JSON.stringify(item)
                var itemStringHex = sakInterface.string2hexString(itemString)
                itemStringList.push(itemStringHex)
            }

            sakSettings.edSetArrayValues(settingKeys.group,
                                        settingKeys.array,
                                        settingKeys.key,
                                        itemStringList)
        }
    }
}
