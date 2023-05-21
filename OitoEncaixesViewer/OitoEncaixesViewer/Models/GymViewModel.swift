//
//  GymViewModel.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import SwiftUI

class GymViewModel: ObservableObject {
    private var logData: [String] = []
    @Published var userModels: [UserViewModel] = []
    @Published var machineModels: [MachineViewModel] = []
    private var numberMachines: Int = 0
    private var totalExercises: Int = 0
    @Published var waitingList: [UserViewModel] = []
    @Published var userOutsideGym: UserViewModel?
    var gymCapacity = 0
    
    init() {
        readTxtFile(name: "log")
        createGym()
    }
    
    private func readTxtFile(name: String) {
        do {
            if let path = Bundle.main.path(forResource: name, ofType: "txt"){
                let data = try String(contentsOfFile:path, encoding: String.Encoding(rawValue: NSUTF8StringEncoding))

                let myStrings = data.split(separator: "\r\n").map { String($0) }
                self.logData = myStrings
                print(logData)
            }
        } catch let error as NSError {
            print(error)
        }
    }
    
    private func createUser(id: String) -> UserViewModel {
        let model = UserViewModel(id: id, totalExercises: totalExercises)
        userModels.append(model)
        return model
    }
    
    private func createMachines() {
        let types: [MachineTypes] = [.A, .B, .C, .D, .E, .F]
        for t in 0..<totalExercises {
            let type = types[t]
            for n in 0..<numberMachines {
                machineModels.append(MachineViewModel(id: (type.rawValue + String(n)), type: type))
            }
        }
    }
    
    private func getUserModelIndex(userID: String) -> Int? {
        for i in 0...userModels.count-1 {
            if userModels[i].id == userID {
                return i
            }
        }
        return nil
    }
    
    private func getMachineModelIndex(machineId: String) -> Int? {
        for i in 0...machineModels.count-1 {
            if machineModels[i].id == machineId {
                return i
            }
        }
        return nil
    }
    
    private func getUserId(sentence: String) -> String {
        return String(sentence.prefix(1))
    }
    
    private func getMachineId(sentence: String) -> String {
        let wordsList = sentence.split(separator: " ")
        
        if let machineType = getMachineType(sentence: sentence) {
            if let indexN = wordsList.firstIndex(of: "maquina") {
                let machineId = wordsList[indexN+1].split(separator: ".")
                return String(machineType + machineId[0])
            }
        }
        return "N"
    }
    
    private func getMachineType(sentence: String) -> String? {
        let wordsList = sentence.split(separator: " ")
        if let index = wordsList.firstIndex(of: "Exercicio") {
            let machineType = wordsList[index+1]
            return String(machineType)
        }
        return nil
    }
    
    func executeLogInstructions() {
        var userId: String
        if !logData.isEmpty {
            let i: Int = min(4, logData.count-1)
            
            let log = logData[i]
            print(log)
            userId = getUserId(sentence: log)
            
            userOutsideGym = nil
            
            if log.contains(UserActions.userArrived.rawValue) {
                let user = createUser(id: userId)
                joinWaitingList(user: user)
            }
            else if log.contains(UserActions.userIsUsingMachine.rawValue) {
                if let userIndex = getUserModelIndex(userID: userId) {
                    let machineID = getMachineId(sentence: log)
                    if let machineIndex = getMachineModelIndex(machineId: machineID) {
                        machineModels[machineIndex].isBeignUsedByUser(user: userModels[userIndex])
                        userModels[userIndex].startedExercise()
                        leaveWaitingList(user: userModels[userIndex])
                    }
                }
            }
            else if log.contains(UserActions.userLeaveGym.rawValue) {
                let model = UserViewModel(id: userId, totalExercises: totalExercises)
                model.cantEnterGymisFull()
                userOutsideGym = model
            }
            else if log.contains(UserActions.userFinishedExercise.rawValue) {
                if let userIndex = getUserModelIndex(userID: userId) {
                    let machineID = getMachineId(sentence: log)
                    if let machineIndex = getMachineModelIndex(machineId: machineID) {
                        machineModels[machineIndex].isUnused()
                        userModels[userIndex].completetedAnExercise()
                        joinWaitingList(user: userModels[userIndex])
                        userModels[userIndex].userIsInWaitingList()
                    }
                }
            } else if log.contains(UserActions.userFinishedAllExercises.rawValue) {
                if let userIndex = getUserModelIndex(userID: userId) {
                    leaveGym(user: userModels[userIndex])
                    userOutsideGym = userModels[userIndex]
                }
            }
            
            if i < logData.count {
                logData.remove(at: i)
            }
        }
        
    }
    
    
    private func createGym() {
        self.gymCapacity = Int(logData[1].suffix(1)) ?? 0
        self.numberMachines = Int(logData[2].suffix(1)) ?? 0
        self.totalExercises = Int(logData[3].suffix(1)) ?? 0
        createMachines()
    }
    
    private func leaveWaitingList(user: UserViewModel) {
        var index: Int?
        
        if !waitingList.isEmpty{
            for i in 0...waitingList.count-1 {
                if waitingList[i].id == user.id {
                    index = i
                    break
                }
            }
        }
        if let index = index {
            waitingList.remove(at: index)
        }
    }
    
    private func joinWaitingList(user: UserViewModel) {
        waitingList.append(user)
    }
    
    private func leaveGym(user: UserViewModel) {
        leaveWaitingList(user: user)
    }
}


enum UserActions: String {
    case userArrived = "Entrei na"
    case userIsUsingMachine = "Fazendo Exercicio"
    case userLeaveGym = "Academia esta cheia!! Vai embora!"
    case userFinishedExercise = "Terminou Exercicio"
    case userFinishedAllExercises = "Terminou o treino e vai embora!"
}

enum MachineTypes: String {
    case A = "A"
    case B = "B"
    case C = "C"
    case D = "D"
    case E = "E"
    case F = "F"
    case G = "G"
    case H = "H"
}
