//
//  MachineViewModel.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 18/05/23.
//

import Foundation

class MachineViewModel: ObservableObject, Identifiable {
    var id: String
    private var type: MachineTypes
    var imageName: String
    @Published var isBeignUsed: Bool = false
    @Published var userUsing: UserViewModel?
    
    init(id: String, type: MachineTypes) {
        self.id = id
        self.type = type
        self.imageName = type.rawValue + "machine"
    }
    
    func isBeignUsedByUser(user: UserViewModel) {
        isBeignUsed = true
        userUsing = user
    }
    
    func isUnused() {
        isBeignUsed = false
    }
        
}
