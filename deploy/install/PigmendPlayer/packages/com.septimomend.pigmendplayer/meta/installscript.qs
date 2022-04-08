/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    // constructor
}

/*
 *Component.prototype.installationFinished = function()
 *{
 *}
 */

Component.prototype.createOperations = function()
{
    try {
        component.createOperations();
    } catch (e) {
        console.log(e);
    }

    if (systemInfo.productType === "windows") {
		component.addOperation( "CreateShortcut","@TargetDir@/PigmendPlayer.exe",
			"@StartMenuDir@/PigmendPlayer.lnk", "-param", "workingDirectory=@TargetDir@",
			"iconPath=@TargetDir@/PigmendPlayer.exe","iconId=0", "description=Pigmend media player");
    }
	else if ((systemInfo.kernelType === "linux") || (systemInfo.kernelType === "Linux")) {
		var dir = installer.value("TargetDir");
		component.addOperation("CreateDesktopEntry", "pigmendplayer.desktop",
            "Type=Application\nName=PigmendPlayer\nExec=sh -c \'"+dir+"/PigmendPlayer -c "+dir+"/config/config.ini -x "+dir+"/xml\'\nGenericName=Pigmend media player.\nIcon="+dir+"/pigmend.ico\nTerminal=false\nCategories=Media;Video;Music;Utility;");
		component.addOperation("CreateDesktopEntry", "@TargetDir@/pigmendplayer.desktop",
            "Type=Application\nName=PigmendPlayer\nExec=sh -c \'"+dir+"/PigmendPlayer -c "+dir+"/config/config.ini -x "+dir+"/xml\'\nGenericName=Pigmend media player.\nIcon="+dir+"/pigmend.ico\nTerminal=false\nCategories=Media;Video;Music;Utility;");
    }
}
