#Windows Service Action
#gudjonh@valitor.is
$ServiceInstance = Get-Service $ServiceName

Write-Output "ServiceName   : $ServiceName"
Write-Output "SelectedAction: $SelectedAction"

if ($SelectedAction -eq "Restart-Service") {
    Write-Output "Restarting $ServiceName, stopping..."
    Restart-Service -InputObject $ServiceName -Force
    $ServiceInstance.WaitForStatus('Running','00:01:00')
    Write-Output "Service $ServiceName started."

} ElseIf  ($SelectedAction -eq "Stop-Service") {
    Write-Output "Stop $ServiceName, stopping..."
    Stop-Service -InputObject $ServiceName -Force
    $ServiceInstance.WaitForStatus('Stopped','00:01:00')
    Write-Output "Service $ServiceName stoped."

} ElseIf  ($SelectedAction -eq "Start-Service") {
    Write-Output "Start $ServiceName, starting..."
    Start-Service -InputObject $ServiceName
    $ServiceInstance.WaitForStatus('Running','00:01:00')
    Write-Output "Service $ServiceName started."
}
