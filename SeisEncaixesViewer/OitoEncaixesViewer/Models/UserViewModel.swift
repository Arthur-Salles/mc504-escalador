//
//  UserViewModel.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import Foundation

class UserViewModel: ObservableObject, Identifiable {
    var id: String
    var totalExercisesToDo: Int
    @Published var imageName: String = "happyFace"
    @Published var exercisesFinished: Int = 0
    @Published var isDoingExercise = false
    
    init(id: String, totalExercises: Int) {
        self.id = id
        self.totalExercisesToDo = totalExercises
    }
   
    func completetedAnExercise() {
        exercisesFinished += 1
        isDoingExercise = false
    }
    
    func startedExercise() {
        isDoingExercise = true
        imageName = "happyFace"
    }
    
    func userIsInWaitingList() {
    }
    
    func getPercentegeOfExercisesCompleted() -> Double {
        return Double(exercisesFinished/totalExercisesToDo)
    }
    
    func cantEnterGymisFull() {
        imageName = "sadFace"
    }
}

